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

uint64_t System::get_cpu_type() {
    return fetch_value(CPU_TYPE);
}

uint64_t System::get_cpu_freq() {
    return fetch_value(CPU_FREQ);
}

uint64_t System::get_physical_cpu() {
    return fetch_value(CPU_PHYS_NUMBER);
}

uint64_t System::get_logic_cpu() {
    return fetch_value(CPU_LOGIC_NUMBER);
}

uint64_t System::get_memory() {
    return fetch_value(MEMORY_SIZE);
}


uint64_t System::fetch_value(const char *func_name) {
    uint64_t number = 0;
    size_t size = sizeof(number);
    sysctlbyname(func_name, &number, &size, nullptr, 0);
    return number;
}

void System::beep() {
    std::cout << '\a';
}

char *System::get_cpu_name() {

    // Cannot provide pointer to heep, will have: 11: SIGSEGV
    char buffer[CHAR_BUFFER_SIZE];
    size_t size = sizeof(buffer);
    sysctlbyname(CPU_NAME, &buffer, &size, nullptr, 0);
    char *result = new char[CHAR_BUFFER_SIZE];
    std::copy(buffer, buffer + size, result);
    return result;
}