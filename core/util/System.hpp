//
// Created by alus on 08.03.2021.
//

#ifndef CPLUSPLUS_SYSTEM_HPP
#define CPLUSPLUS_SYSTEM_HPP

#include <memory>
#include "../smc/smc.h"
#include "../types/types.hpp"

class System {

public:

    static uint64_t getCpuType();

    static uint64_t getCpuFreq();

    static uint64_t getPhysicalCpuCores();

    static uint64_t getLogicCpuCores();

    static uint64_t getMemory();

    static void beep();

    static std::unique_ptr<char[]> getCpuName();

private:
    static uint64_t fetchValue(const char *funcName);
};


#endif //CPLUSPLUS_SYSTEM_HPP
