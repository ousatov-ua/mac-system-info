//
// Created by alus on 11.03.2021.
//

#ifndef SYSTEM_INFO_CONTROLLER_HPP
#define SYSTEM_INFO_CONTROLLER_HPP

#include "../../system/SystemInfo.hpp"
#include "UI.hpp"
#include <memory>

class Controller {
public:
    Controller();
    void display(SystemInfo&);
private:
    std::unique_ptr<UI> ui;
};


#endif //SYSTEM_INFO_CONTROLLER_HPP
