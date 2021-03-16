#include <iostream>
#include "core/SystemInfo.hpp"
#include "ui/console/Controller.hpp"

void print_help();

int main(int argc, char *argv[]) {
    SystemInfo systemInfo;
    if (argc == 1 || (argc == 2 && strcmp("--help", argv[1]) == 0)) {
        print_help();
        return 0;
    } else if (strcmp("--console", argv[1]) == 0) {
        std::cout << systemInfo.toString() << std::endl;
        return 0;
    } else if (strcmp("--ui", argv[1]) == 0) {
        Controller controller;
        controller.display(systemInfo);
        return 0;
    }
    print_help();
    return 0;
}

void print_help() {
    cout << "Possible arguments:" << endl;
    cout << "--help   : print this help" << endl;
    cout << "--ui     : run with UI (ncurses)" << endl;
    cout << "--console: run once in console mode" << endl;
}
