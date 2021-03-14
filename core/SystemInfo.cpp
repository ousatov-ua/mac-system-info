//
// Created by alus on 08.03.2021.
//

#include "SystemInfo.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include "smc/smc.h"

#define INDENT 4

SystemInfo::SystemInfo() : processor(std::make_unique<Processor>()), memory(std::make_unique<Memory>()),
                           fans_info(std::make_unique<FansInfo>()),
                           gpu(std::make_unique<Gpu>()) {
    SmcLib.SMCOpen();
}

std::string SystemInfo::toString() {
    return toJson().dump(INDENT);
}

SystemInfo::~SystemInfo() {
    SmcLib.SMCClose();
}

nlohmann::ordered_json SystemInfo::toJson() {
    nlohmann::ordered_json res;
    const string name = "system_info";
    res[name]["cpu"] = processor->to_json();
    res[name]["memory"] = memory->to_json();
    res[name]["fans"] = fans_info->to_json();
    res[name]["gpu"] = gpu->to_json();
    return res;
}
