//
// Created by alus on 11.03.2021.
//

#include "Controller.hpp"
#include <unistd.h>

#define REFRESH_MICRO_SECONDS 5000000

bool Controller::terminated = false;

void Controller::display(SystemInfo &systemInfo) {
    while (!Controller::terminated) {
        auto json = systemInfo.to_json();
        ui->show(json);
        usleep(REFRESH_MICRO_SECONDS);
    }
}

Controller::Controller() : ui(std::make_unique<UI>(catch_sig)) {

}

void Controller::catch_sig(int sig) {
    Controller::terminated = true;
}
