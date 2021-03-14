//
// Created by alus on 10.03.2021.
//

#include "Gpu.hpp"
#include "../util/System.hpp"

double Gpu::getTemperature() {
    return SmcLib.SMCGpuTemp();
}

nlohmann::json Gpu::to_json() {
    nlohmann::ordered_json json;
    json["temperature"] = getTemperature();
    return json;
}
