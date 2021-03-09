/*
 * Apple System Management Control (SMC) Tool
 * Copyright (C) 2006 devnull
 * Copyright (C) 2020 theopolis (Teddy Reed)
 * Copyright (C) 2021 alus
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <IOKit/IOKitLib.h>
#include <stdio.h>

#include "smc.h"

static io_connect_t conn;

UInt8 fannum[] = "0123456789ABCDEFGHIJ";

UInt32 c_strtoul(const char *str, int size, int base) {
    UInt32 total = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (base == 16)
            total += str[i] << (size - 1 - i) * 8;
        else
            total += (unsigned char) (str[i] << (size - 1 - i) * 8);
    }
    return total;
}

void c_ultostr(char *str, UInt32 val) {
    str[0] = '\0';
    sprintf(str, "%c%c%c%c",
            (unsigned int) val >> 24,
            (unsigned int) val >> 16,
            (unsigned int) val >> 8,
            (unsigned int) val);
}

kern_return_t SMCOpen() {
    kern_return_t result;
    io_iterator_t iterator;
    io_object_t device;

    CFMutableDictionaryRef matchingDictionary = IOServiceMatching("AppleSMC");
    result = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDictionary, &iterator);
    if (result != kIOReturnSuccess) {
        printf("Error: IOServiceGetMatchingServices() = %08x\n", result);
        return 1;
    }

    device = IOIteratorNext(iterator);
    IOObjectRelease(iterator);
    if (device == 0) {
        printf("Error: no SMC found\n");
        return 1;
    }

    result = IOServiceOpen(device, mach_task_self(), 0, &conn);
    IOObjectRelease(device);
    if (result != kIOReturnSuccess) {
        printf("Error: IOServiceOpen() = %08x\n", result);
        return 1;
    }

    return kIOReturnSuccess;
}

kern_return_t SMCClose() {
    return IOServiceClose(conn);
}

kern_return_t SMCCall(int index, SMCKeyData_t *inputStructure, SMCKeyData_t *outputStructure) {
    size_t structureInputSize;
    size_t structureOutputSize;

    structureInputSize = sizeof(SMCKeyData_t);
    structureOutputSize = sizeof(SMCKeyData_t);

#if MAC_OS_X_VERSION_10_5
    return IOConnectCallStructMethod(conn, index,
            // inputStructure
                                     inputStructure, structureInputSize,
            // ouputStructure
                                     outputStructure, &structureOutputSize);
#else
    return IOConnectMethodStructureIStructureO(conn, index,
        structureInputSize, /* structureInputSize */
        &structureOutputSize, /* structureOutputSize */
        inputStructure, /* inputStructure */
        outputStructure); /* ouputStructure */
#endif
}

kern_return_t SMCReadKey(UInt32Char_t key, SMCVal_t *val) {
    kern_return_t result;
    SMCKeyData_t inputStructure;
    SMCKeyData_t outputStructure;

    memset(&inputStructure, 0, sizeof(SMCKeyData_t));
    memset(&outputStructure, 0, sizeof(SMCKeyData_t));
    memset(val, 0, sizeof(SMCVal_t));

    inputStructure.key = c_strtoul(key, 4, 16);
    inputStructure.data8 = SMC_CMD_READ_KEYINFO;

    result = SMCCall(KERNEL_INDEX_SMC, &inputStructure, &outputStructure);
    if (result != kIOReturnSuccess)
        return result;

    val->dataSize = outputStructure.keyInfo.dataSize;
    c_ultostr(val->dataType, outputStructure.keyInfo.dataType);
    inputStructure.keyInfo.dataSize = val->dataSize;
    inputStructure.data8 = SMC_CMD_READ_BYTES;

    result = SMCCall(KERNEL_INDEX_SMC, &inputStructure, &outputStructure);
    if (result != kIOReturnSuccess)
        return result;

    memcpy(val->bytes, outputStructure.bytes, sizeof(outputStructure.bytes));

    return kIOReturnSuccess;
}

double SMCGetTemperature(char *key) {
    SMCVal_t val;
    kern_return_t result;

    result = SMCReadKey(key, &val);
    if (result == kIOReturnSuccess) {
        // read succeeded - check returned value
        if (val.dataSize > 0) {
            if (strcmp(val.dataType, DATATYPE_SP78) == 0) {
                // convert sp78 value to temperature
                int intValue = val.bytes[0] * 256 + (unsigned char) val.bytes[1];
                return intValue / 256.0;
            }
        }
    }
    // read failed
    return 0.0;
}

/**
 * Read CPU temperature
 * @return CPU temp
 */
double readCpuTemp() {
    return SMCGetTemperature(SMC_KEY_CPU_TEMP);
}

/**
 * Read GPU temperature
 * @return GPU temp
 */
double readGpuTemp() {
    return SMCGetTemperature(SMC_KEY_GPU_TEMP);
}

int c_strtof(const char *str, int size, int e) {
    int total = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (i == (size - 1))
            total += (str[i] & 0xff) >> e;
        else
            total += str[i] << (size - 1 - i) * (8 - e);
    }

    return total;
}

int getFloatFromVal(SMCVal_t val) {
    int f_val = -1;

    if (val.dataSize > 0) {
        if (strcmp(val.dataType, DATATYPE_FLT) == 0 && val.dataSize == 4) {
            memcpy(&f_val, val.bytes, sizeof(float));
        } else if (strcmp(val.dataType, DATATYPE_FPE2) == 0 && val.dataSize == 2) {
            f_val = c_strtof(val.bytes, val.dataSize, 2);
        } else if (strcmp(val.dataType, DATATYPE_UINT16) == 0 && val.dataSize == 2) {
            f_val = c_strtoul((char *) val.bytes, val.dataSize, 10);
        } else if (strcmp(val.dataType, DATATYPE_UINT8) == 0 && val.dataSize == 1) {
            f_val = c_strtoul((char *) val.bytes, val.dataSize, 10);
        }
    }
    return f_val;
}

/**
 * Get array of Fans and their data
 * @return array of Fan_t. This is a data in heep, so be careful
 */
Fan_t *SMCFans(void) {
    kern_return_t result;
    SMCVal_t val;
    UInt32Char_t key;
    int totalFans, i;

    Fan_t *fans = malloc(sizeof(Fan_t));
    result = SMCReadKey("FNum", &val);
    if (result != kIOReturnSuccess)
        return fans;

    totalFans = c_strtoul((char *) val.bytes, val.dataSize, 10);

    fans = malloc(sizeof(Fan_t) * totalFans);
    for (i = 0; i < totalFans; i++) {
        Fan_t f;
        f.number = i;
        f.number = fannum[i];
        SMCReadKey(key, &val);
        if (val.dataSize > 0) {
            memcpy(f.name, val.bytes, sizeof(val.bytes));
        }
        SMCReadKey(key, &val);
        f.actual_speed = getFloatFromVal(val);
        SMCReadKey(key, &val);
        f.minimal_speed = getFloatFromVal(val);
        SMCReadKey(key, &val);
        f.maximum_speed = getFloatFromVal(val);
        SMCReadKey(key, &val);
        f.safe_speed = getFloatFromVal(val);
        SMCReadKey(key, &val);
        f.target_speed = getFloatFromVal(val);
        SMCReadKey("FS! ", &val);
        if (val.dataSize > 0) {
            if ((c_strtoul((char *) val.bytes, 2, 16) & (1 << i)) == 0) {
                f.mode = CPU_AUTO
            } else {
                f.mode = CPU_FORCED
            }
        } else {
            SMCReadKey(key, &val);
            if (getFloatFromVal(val)) {
                f.mode = CPU_FORCED
            } else {
                f.mode = CPU_AUTO
            }
        }
        fans[i] = f;
    }
    return fans;
}
