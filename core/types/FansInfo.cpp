//
// Created by alus on 09.03.2021.
//

#include <iostream>
#include "FansInfo.hpp"
#include <string>
#include <sstream>

void FansInfo::update() {
    fans_info_ = SmcLib.SMCFans();
}

nlohmann::json FansInfo::toJson() {
    update();
    nlohmann::ordered_json res;
    for (int i = 0; i < fans_info_.size; i++) {
        auto fan = fans_info_.fans[i];
        std::stringstream ss;
        ss << fan.name;
        std::string name;
        ss >> name;
        res[i]["id"] = fan.id;
        res[i]["name"] = name;
        res[i]["actual_speed"]["rpm"] = fan.actual_speed;
        res[i]["minimal_speed"]["rpm"] = fan.minimal_speed;
        res[i]["maximum_speed"]["rpm"] = fan.maximum_speed;
        res[i]["safe_speed"]["rpm"]= fan.safe_speed;
        res[i]["target_speed"]["rpm"] = fan.target_speed;
        res[i]["mode"] = fan.mode == FAN_FORCED ? "forced" : "auto";
    }
    return res;
}
