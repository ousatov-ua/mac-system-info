//
// Created by alus on 11.03.2021.
//

#include "UI.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <memory>
#include <iostream>

#define KEY_QUIT 113

void UI::show(nlohmann::ordered_json &json) {
    getmaxyx(UI::window, max_y, max_x);
    attrset(COLOR_PAIR(1));
    clear_line(2, max_x);
    std::string s = std::string("Temperature: ") + json["system_info"]["cpu"]["temperature"].dump();
    const char *value = s.c_str();
    mvaddstr(2, 0, value);
    curs_set(0);
    refresh();
}

WINDOW *UI::window = nullptr;
int UI::max_x = 0;
int UI::max_y = 0;
bool UI::terminated = false;

UI::UI() {
    signal(SIGINT, catch_sig);
    initscr();
    keypad(stdscr, true);
    nonl();
    cbreak();
    noecho();

    UI::window = newwin(0, 0, 0, 0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLUE);
        init_pair(3, COLOR_BLACK, COLOR_CYAN);
    }
    process();
}

void UI::catch_sig(int sig) {
    UI::terminated = true;
}

void UI::process() {
    getmaxyx(UI::window, max_y, max_x);

    attrset(COLOR_PAIR(1));
    for (int i = 0; i <= max_y; i++) {
        clear_line(i, max_x);
    }

    // Draw header
    attrset(A_BOLD | COLOR_PAIR(2));
    clear_line(0, max_x);
    mvaddstr(0, 0, "System Info");

    // Draw body
    attrset(COLOR_PAIR(1));
    clear_line(1, max_x);
    mvaddstr(1, 0, "CPU");

    // Draw status line
    attrset(A_BOLD | COLOR_PAIR(2));
    clear_line(max_y - 2, max_x);
    mvaddstr(max_y - 2, 0, "Alus Production 2021");

    curs_set(0);
    refresh();

    /*int last_key = getch();
    if (last_key == KEY_QUIT) {
        UI::terminated = true;
    }*/
}

void UI::clear_line(int y, int l) {
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