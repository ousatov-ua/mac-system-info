//
// Created by alus on 08.03.2021.
//

#include "SystemInfo.hpp"
#include "string"
#include <nlohmann/json.hpp>
#include "smc/smc.h"

SystemInfo::SystemInfo() : processor(new Processor()), memory(new Memory()) {
    SMCOpen();
}

std::string SystemInfo::to_string() {
    nlohmann::json res;
    const string name = "system_info";
    res[name]["cpu"] = processor->to_json();
    res[name]["memory"] = memory->to_json();
    return res.dump(4);
}

SystemInfo::~SystemInfo() {
    SMCClose();
    delete processor;
    delete memory;
}
