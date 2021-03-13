//
// Created by alus on 11.03.2021.
//

#ifndef SYSTEM_INFO_CONTROLLER_HPP
#define SYSTEM_INFO_CONTROLLER_HPP

#include "../../core/SystemInfo.hpp"
#include "UI.hpp"
#include <memory>

class Controller {
public:
    Controller();

    void display(SystemInfo &);

    static void catch_sig(int);

private:
    std::unique_ptr<UI> ui;
    static bool terminated;
};


#endif //SYSTEM_INFO_CONTROLLER_HPP
