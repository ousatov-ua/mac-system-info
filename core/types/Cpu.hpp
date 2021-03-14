//
// Created by alus on 08.03.2021.
//

#ifndef SYSTEM_INFO_CPU_HPP
#define SYSTEM_INFO_CPU_HPP

#include "types.hpp"
#include <string>
#include "nlohmann/json.hpp"
#include <mach/machine.h>

class Cpu {
public:
    const uint64_t physCores;
    const uint64_t logicalCores;
    const uint64_t freq;
    const uint64_t type;
    const std::unique_ptr<char[]> name;

    static double getTemperature();

    std::string getType() const;

    Cpu();

    ~ Cpu();

    nlohmann::json toJson();
};


#endif //SYSTEM_INFO_CPU_HPP
