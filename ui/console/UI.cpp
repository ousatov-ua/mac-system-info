//
// Created by alus on 11.03.2021.
//

#include <iostream>
#include "UI.hpp"

void UI::show(nlohmann::ordered_json &json) {
    std::cout << json << std::endl;
}

UI::UI() {
    std::cout << "CPU" << std::endl;
}