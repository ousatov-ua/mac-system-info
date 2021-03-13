//
// Created by alus on 11.03.2021.
//

#ifndef SYSTEM_INFO_UI_HPP
#define SYSTEM_INFO_UI_HPP

#include <nlohmann/json.hpp>
#include "ncurses.h"

using catch_sig_func = void (*)(int);

class UI {
public:
    explicit UI(catch_sig_func);

    ~UI();

    void show(nlohmann::ordered_json &);

private:
    WINDOW *window;

    void process();

    void clear_line(int y, int l);

    int max_x;
    int max_y;
};


#endif //SYSTEM_INFO_UI_HPP
