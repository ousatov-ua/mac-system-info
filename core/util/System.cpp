//
// Created by alus on 08.03.2021.
//

#include "System.hpp"

#define CPU_TYPE "hw.cputype"
#define CPU_FREQ "hw.cpufrequency"
#define CPU_PHYS_NUMBER "hw.physicalcpu"
#define CPU_LOGIC_NUMBER "hw.logicalcpu"
#define MEMORY_SIZE "hw.memsize"
#define CPU_NAME "machdep.cpu.brand_string"
#define CHAR_BUFFER_SIZE 1024

#include <sys/sysctl.h>
#include <iostream>
#include <array>

uint64_t System::getCpuType() {
    return fetchValue(CPU_TYPE);
}

uint64_t System::getCpuFreq() {
    return fetchValue(CPU_FREQ);
}

uint64_t System::getPhysicalCpuCores() {
    return fetchValue(CPU_PHYS_NUMBER);
}

uint64_t System::getLogicCpuCores() {
    return fetchValue(CPU_LOGIC_NUMBER);
}

uint64_t System::getMemory() {
    return fetchValue(MEMORY_SIZE);
}


uint64_t System::fetchValue(const char *func_name) {
    uint64_t number = 0;
    size_t size = sizeof(number);
    sysctlbyname(func_name, &number, &size, nullptr, 0);
    return number;
}

void System::beep() {
    std::cout << '\a';
}

std::unique_ptr<char[]> System::getCpuName() {
    auto buffer = std::make_unique<char[]>(CHAR_BUFFER_SIZE);
    size_t size = sizeof(char) * CHAR_BUFFER_SIZE;
    sysctlbyname(CPU_NAME, buffer.get(), &size, nullptr, 0);
    return buffer;
}
