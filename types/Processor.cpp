//
// Created by alus on 08.03.2021.
//

#include "Processor.hpp"
#include "../util/System.hpp"
#include <nlohmann/json.hpp>
#include <mach/machine.h>
#include "../smc/smc.h"

Processor::Processor() : cpu_phys_number(System::get_physical_cpu()),
                         cpu_logical_number(System::get_logic_cpu()),
                         cpu_freq(System::get_cpu_freq()),
                         cpu_type(System::get_cpu_type()),
                         cpu_name(System::get_cpu_name()) {

}

Processor::~Processor() = default;

std::string Processor::get_cpu_type() const {
    if (CPU_TYPE_I860 == cpu_type) {
        return std::string("I860");
    } else if (CPU_TYPE_X86 == cpu_type) {
        return std::string("Intel");
    }
    return std::to_string(cpu_type);
}

double Processor::get_cpu_temp() {
    return readCpuTemp();
}

nlohmann::json Processor::to_json() {
    nlohmann::json res;
    res["name"] = cpu_name.get();
    res["type"] = cpu_type;
    res["type_name"] = get_cpu_type();
    res["phys_number"] = cpu_phys_number;
    res["logical_number"] = cpu_logical_number;
    res["freq"] = cpu_freq;
    res["temp"] = get_cpu_temp();
    return res;
}

