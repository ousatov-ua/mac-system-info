//
// Created by alus on 11.03.2021.
//

#include "UI.hpp"
#include <ncurses.h>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

#define row(json, title, data) std::string(title) + json[data].dump()
#define row_double(json, title, data) std::string(title) + roundDouble(data)
#define EMPTY_ROW ""

void UI::show(nlohmann::ordered_json &json) {
    getmaxyx(this->window_, max_y_, max_x_);

    attrset(COLOR_PAIR(1));
    for (int i = 0; i <= max_y_; i++) {
        clearLine(i, max_x_);
    }

    // Draw header
    attrset(A_BOLD | COLOR_PAIR(2));
    clearLine(0, max_x_);
    mvaddstr(0, 0, " SYSTEM INFO");

    // Draw status line
    attrset(A_BOLD | COLOR_PAIR(2));
    clearLine(max_y_ - 2, max_x_);
    mvaddstr(max_y_ - 2, 0, " Alus Production 2021. Ctrl+C to Exit");

    auto cpu = json["system_info"]["cpu"];
    attrset(COLOR_PAIR(1));
    writeData(EMPTY_ROW, 1);
    attrset(COLOR_PAIR(3));
    writeData(" Cpu", 2);
    attrset(COLOR_PAIR(1));
    writeData(row(cpu, " Name              : ", "name"), 3);
    writeData(row(cpu, " Logical Cores     : ", "logical_cores"), 4);
    writeData(row(cpu, " Physical Cores    : ", "phys_cores"), 5);
    writeData(row_double(cpu, " Temperature(C)    : ", cpu["temperature"]["celsius"]), 6);

    writeData(EMPTY_ROW, 7);

    attrset(COLOR_PAIR(3));
    writeData(" GPU", 8);
    attrset(COLOR_PAIR(1));
    auto gpu = json["system_info"]["gpu"];
    writeData(row_double(gpu, " Temperature(C)    : ", gpu["temperature"]["celsius"]), 9);

    writeData(EMPTY_ROW, 10);

    attrset(COLOR_PAIR(3));

    auto fans = json["system_info"]["fans"];
    std::string fans_title = std::string(" Fans (total ") + std::to_string(fans.size()) + ")";
    writeData(fans_title, 11);
    attrset(COLOR_PAIR(1));

    int start = 12;
    int rows = 8;
    for (int i = 0; i < fans.size(); i++) {
        auto fan = fans.at(i);
        writeData(row(fan, " Id                : ", "id"), start + rows * i + i);
        writeData(row(fan, " Name              : ", "name"), start + rows * i + 1 + i);
        writeData(row_double(fan, " Max speed(rpm)    : ", fan["maximum_speed"]["rpm"]), start + rows * i + 2 + i);
        writeData(row_double(fan, " Min speed(rpm)    : ", fan["minimal_speed"]["rpm"]), start + rows * i + 3 + i);
        writeData(row_double(fan, " Actual speed(rpm) : ", fan["actual_speed"]["rpm"]), start + rows * i + 4 + i);
        writeData(row_double(fan, " Target speed(rpm) : ", fan["target_speed"]["rpm"]), start + rows * i + 5 + i);
        writeData(row(fan, " Mode              : ", "mode"), start + rows * i + 6 + i);
    }
    curs_set(0);
    refresh();


    /*int last_key = getch();
    if (last_key == KEY_QUIT) {
        Controller::terminated = true;
    }*/
}

std::string UI::roundDouble(double value) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    return stream.str();
}

void UI::writeData(const std::string &data, int line) {
    clearLine(line, max_x_);
    const char *value = data.c_str();
    mvaddstr(line, 0, value);
}

UI::UI(catchSigFunc catch_sig) : max_x_(0), max_y_(0) {
    signal(SIGINT, catch_sig);
    initscr();
    keypad(stdscr, true);
    nonl();
    cbreak();
    noecho();

    this->window_ = newwin(0, 0, 0, 0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLUE);
        init_pair(3, COLOR_BLACK, COLOR_CYAN);
    }
}

void UI::clearLine(int y, int l) {
    move(y, 1);
    l++;
    char str[l];
    for (int i = 0; i < l; i++) {
        str[i] = ' ';
    }
    str[l - 1] = '\0';
    mvaddstr(y, 0, str);
}

UI::~UI() {
    endwin();
}

