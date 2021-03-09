//
// Created by alus on 08.03.2021.
//

#ifndef SYSTEM_INFO_DATA_HPP
#define SYSTEM_INFO_DATA_HPP

#include "nlohmann/json.hpp"

class Data {
public:
    __unused virtual nlohmann::json to_json() = 0;
};


#endif //SYSTEM_INFO_DATA_HPP
