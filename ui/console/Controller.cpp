//
// Created by alus on 11.03.2021.
//

#include "Controller.hpp"

void Controller::display(SystemInfo &systemInfo) {
    auto json = systemInfo.to_json();
    ui->show(json);
}

Controller::Controller() : ui(std::make_unique<UI>()) {

}
