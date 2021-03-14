//
// Created by alus on 08.03.2021.
//

#include "Memory.hpp"

#include "../util/System.hpp"

Memory::Memory() : memory(System::getMemory()) {

}

nlohmann::json Memory::to_json() {
    nlohmann::ordered_json res;
    res["memory"] = memory;
    return res;
}
