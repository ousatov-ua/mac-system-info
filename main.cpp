#include "system/SystemInfo.hpp"
#include "ui/console/Controller.hpp"

int main() {
    Controller controller;
    SystemInfo systemInfo;
    controller.display(systemInfo);
    return 0;
}