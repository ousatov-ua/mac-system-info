//
// Created by alus on 11.03.2021.
//

#include "Controller.hpp"
#include <unistd.h>

#define REFRESH_MICRO_SECONDS 5000000

void Controller::display(SystemInfo &systemInfo) {
    while (!UI::terminated) {
        auto json = systemInfo.to_json();
        ui->show(json);
        usleep(REFRESH_MICRO_SECONDS);
    }
}

Controller::Controller() : ui(std::make_unique<UI>()) {

}
