//
// Created by alus on 08.03.2021.
//

#include "Cpu.hpp"
#include "../util/System.hpp"
#include <nlohmann/json.hpp>
#include <mach/machine.h>

Cpu::Cpu() : physCores(System::getPhysicalCpuCores()),
             logicalCores(System::getLogicCpuCores()),
             freq(System::getCpuFreq()),
             type(System::getCpuType()),
             name(System::getCpuName()) {

}

Cpu::~Cpu() = default;

std::string Cpu::getType() const {
    if (CPU_TYPE_I860 == type) {
        return std::string("I860");
    } else if (CPU_TYPE_X86 == type) {
        return std::string("Intel");
    }
    return std::to_string(type);
}

double Cpu::getTemperature() {
    return SmcLib.SMCCpuTemp();
}

nlohmann::json Cpu::toJson() {
    nlohmann::ordered_json res;
    res["name"] = name.get();
    res["type"] = type;
    res["phys_cores"] = physCores;
    res["logical_cores"] = logicalCores;
    res["freq"] = freq;
    res["temperature"] = getTemperature();
    return res;
}

