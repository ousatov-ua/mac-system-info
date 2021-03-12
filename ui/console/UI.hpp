//
// Created by alus on 11.03.2021.
//

#ifndef SYSTEM_INFO_UI_HPP
#define SYSTEM_INFO_UI_HPP

#include <nlohmann/json.hpp>
#include "ncurses.h"

typedef void (*catch_sig_func)(int);

class UI {
public:
    explicit UI(catch_sig_func);

    ~UI();

    static void show(nlohmann::ordered_json &);

private:
    static WINDOW *window;

    static void process();

    static int max_x;
    static int max_y;

    static void clear_line(int y, int l);
};


#endif //SYSTEM_INFO_UI_HPP
