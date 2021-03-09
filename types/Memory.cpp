//
// Created by alus on 08.03.2021.
//

#include "Memory.hpp"

#include "../System.hpp"

Memory::Memory() : memory(System::get_memory()) {

}

nlohmann::json Memory::to_json() {
    nlohmann::json res;
    res["memory"] = memory;
    return res;
}
