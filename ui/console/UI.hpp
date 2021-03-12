//
// Created by alus on 11.03.2021.
//

#ifndef SYSTEM_INFO_UI_HPP
#define SYSTEM_INFO_UI_HPP

#include <nlohmann/json.hpp>
#include "ncurses.h"

class UI {
public:
    UI();

    ~UI();

    void show(nlohmann::ordered_json &);
    static bool terminated;
private:
    static WINDOW * window;
    static void catch_sig(int);
    static void process();
    static int max_x;
    static int max_y;
    static void clear_line(int y, int l);
};


#endif //SYSTEM_INFO_UI_HPP
