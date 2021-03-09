//
// Created by alus on 08.03.2021.
//

#include "SystemInfo.hpp"
#include "string"
#include <nlohmann/json.hpp>
#include <memory>
#include "smc/smc.h"

SystemInfo::SystemInfo() : processor(std::make_unique<Processor>()), memory(std::make_unique<Memory>()) {
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
}
