//
// Created by alus on 11.03.2021.
//

#ifndef SYSTEM_INFO_UI_HPP
#define SYSTEM_INFO_UI_HPP
#include <nlohmann/json.hpp>

class UI {
public:
    UI();
    void show(nlohmann::ordered_json&);
};


#endif //SYSTEM_INFO_UI_HPP
