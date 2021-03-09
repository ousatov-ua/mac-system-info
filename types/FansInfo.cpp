//
// Created by alus on 09.03.2021.
//

#include <iostream>
#include "FansInfo.hpp"
#include <string>
#include <sstream>

void FansInfo::update() {
    fans_info = SMCFans();
}

nlohmann::json FansInfo::to_json() {
    update();
    nlohmann::json res;
    for (int i = 0; i < fans_info.size; i++) {
        auto fan = fans_info.fans[i];
        std::stringstream ss;
        ss<<fan.name;
        std::string name;
        ss>>name;
        res[i]["id"] = fan.id;
        res[i]["actual_speed"] = fan.actual_speed;
        res[i]["minimal_speed"] = fan.minimal_speed;
        res[i]["maximum_speed"] = fan.maximum_speed;
        res[i]["safe_speed"] = fan.safe_speed;
        res[i]["target_speed"] = fan.target_speed;
        res[i]["name"] = name;
    }
    return res;
}
