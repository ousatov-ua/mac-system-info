//
// Created by alus on 08.03.2021.
//

#include "Memory.hpp"

#include "../util/System.hpp"

Memory::Memory() : memory_(System::getMemory()) {

}

nlohmann::json Memory::toJson() {
    nlohmann::ordered_json res;
    res["memory_"] = memory_;
    return res;
}
