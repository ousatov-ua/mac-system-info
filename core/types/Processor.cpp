//
// Created by alus on 08.03.2021.
//

#include "Processor.hpp"
#include "../util/System.hpp"
#include <nlohmann/json.hpp>
#include <mach/machine.h>

Processor::Processor() : physCores(System::getPhysicalCpuCores()),
                         logicalCores(System::getLogicCpuCores()),
                         freq(System::getCpuFreq()),
                         type(System::getCpuType()),
                         name(System::getCpuName()) {

}

Processor::~Processor() = default;

std::string Processor::getType() const {
    if (CPU_TYPE_I860 == type) {
        return std::string("I860");
    } else if (CPU_TYPE_X86 == type) {
        return std::string("Intel");
    }
    return std::to_string(type);
}

double Processor::getTemperature() {
    return SmcLib.SMCCpuTemp();
}

nlohmann::json Processor::toJson() {
    nlohmann::ordered_json res;
    res["name"] = name.get();
    res["type"] = type;
    res["phys_cores"] = physCores;
    res["logical_cores"] = logicalCores;
    res["freq"] = freq;
    res["temperature"] = getTemperature();
    return res;
}

