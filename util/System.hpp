//
// Created by alus on 08.03.2021.
//

#ifndef CPLUSPLUS_SYSTEM_HPP
#define CPLUSPLUS_SYSTEM_HPP

#include <memory>
#include "../smc/smc.h"
#include "../common/types.hpp"

#define CELCIUS "˚C"

class System {

public:

    static uint64_t get_cpu_type();

    static uint64_t get_cpu_freq();

    static uint64_t get_physical_cpu();

    static uint64_t get_logic_cpu();

    static uint64_t get_memory();

    static void beep();

    static std::unique_ptr<char[]> get_cpu_name();

    static Fan_info get_fan_info();

private:
    static uint64_t fetch_value(const char *func_name);
};


#endif //CPLUSPLUS_SYSTEM_HPP
