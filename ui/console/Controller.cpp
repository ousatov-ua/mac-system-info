//
// Created by alus on 11.03.2021.
//

#include "Controller.hpp"
#include <unistd.h>

void Controller::display(SystemInfo &systemInfo) {
    while (!UI::terminated) {
        auto json = systemInfo.to_json();
        ui->show(json);
        usleep(5000000);
    }
}

Controller::Controller() : ui(std::make_unique<UI>()) {

}
