//
// Created by alus on 08.03.2021.
//

#include "SystemInfo.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include "smc/smc.h"

SystemInfo::SystemInfo() : processor(std::make_unique<Processor>()), memory(std::make_unique<Memory>()),
                           fans_info(std::make_unique<FansInfo>()),
                           gpu(std::make_unique<Gpu>()) {
    SMCOpen();
}

std::string SystemInfo::to_string() {
    return to_json().dump(4);
}

SystemInfo::~SystemInfo() {
    SMCClose();
}

nlohmann::ordered_json SystemInfo::to_json() {
    nlohmann::ordered_json res;
    const string name = "system_info";
    res[name]["cpu"] = processor->to_json();
    res[name]["memory"] = memory->to_json();
    res[name]["fans"] = fans_info->to_json();
    res[name]["gpu"] = gpu->to_json();
    return res;
}
