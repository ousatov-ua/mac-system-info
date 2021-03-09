//
// Created by alus on 08.03.2021.
//

#ifndef SYSTEM_INFO_PROCESSOR_HPP
#define SYSTEM_INFO_PROCESSOR_HPP

#include "../common/types.hpp"
#include <string>
#include "nlohmann/json.hpp"
#include <mach/machine.h>

class Processor {
public:
    const uint64_t cpu_phys_number;
    const uint64_t cpu_logical_number;
    const uint64_t cpu_freq;
    const uint64_t cpu_type;
    const char *cpu_name;

    static double get_cpu_temp();


    std::string get_cpu_type() const;

    Processor();

    ~ Processor();

    nlohmann::json to_json();

};


#endif //SYSTEM_INFO_PROCESSOR_HPP
