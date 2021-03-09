#include <iostream>
#include "SystemInfo.hpp"

using namespace std;

int main() {
    SystemInfo systemInfo;
    std::cout << systemInfo.to_string() << endl;
    return 0;
}