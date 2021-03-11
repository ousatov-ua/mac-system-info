//
// Created by alus on 10.03.2021.
//

#ifndef SYSTEM_INFO_GPU_HPP
#define SYSTEM_INFO_GPU_HPP


#include <nlohmann/json.hpp>
#include "Data.hpp"

class Gpu : public Data {

public:
    static double getTemperature();

    nlohmann::json to_json() override;
};


#endif //SYSTEM_INFO_GPU_HPP
