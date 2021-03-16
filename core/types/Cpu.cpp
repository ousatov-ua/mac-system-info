//
// Created by alus on 08.03.2021.
//

#include "Cpu.hpp"
#include "../util/System.hpp"
#include <nlohmann/json.hpp>
#include <mach/machine.h>

Cpu::Cpu() : phys_cores_(System::getPhysicalCpuCores()),
             logical_cores_(System::getLogicCpuCores()),
             freq_(System::getCpuFreq()),
             type_(System::getCpuType()),
             name_(System::getCpuName()) {

}

Cpu::~Cpu() = default;

std::string Cpu::getType() const {
    if (CPU_TYPE_I860 == type_) {
        return std::string("I860");
    } else if (CPU_TYPE_X86 == type_) {
        return std::string("Intel");
    }
    return std::to_string(type_);
}

double Cpu::getTemperature() {
    return SmcLib.SMCCpuTemp();
}

nlohmann::json Cpu::toJson() {
    nlohmann::ordered_json res;
    res["name"] = name_.get();
    res["type"] = type_;
    res["phys_cores"] = phys_cores_;
    res["logical_cores"] = logical_cores_;
    res["freq"] = freq_;
    res["temperature"]["celsius"] = getTemperature();
    return res;
}

