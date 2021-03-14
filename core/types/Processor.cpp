//
// Created by alus on 08.03.2021.
//

#include "Processor.hpp"
#include "../util/System.hpp"
#include <nlohmann/json.hpp>
#include <mach/machine.h>

Processor::Processor() : cpu_phys_number(System::getPhysicalCpuCores()),
                         cpu_logical_number(System::getLogicCpuCores()),
                         cpu_freq(System::getCpuFreq()),
                         cpu_type(System::getCpuType()),
                         cpu_name(System::getCpuName()) {

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

double Processor::get_cpu_temperature() {
    return SmcLib.SMCCpuTemp();
}

nlohmann::json Processor::to_json() {
    nlohmann::ordered_json res;
    res["name"] = cpu_name.get();
    res["type"] = cpu_type;
    res["phys_cores"] = cpu_phys_number;
    res["logical_cores"] = cpu_logical_number;
    res["freq"] = cpu_freq;
    res["temperature"] = get_cpu_temperature();
    return res;
}

