//
// Created by alus on 08.03.2021.
//

#ifndef SYSTEM_INFO_MEMORY_HPP
#define SYSTEM_INFO_MEMORY_HPP

#include "../common/types.hpp"
#include "Data.hpp"

class Memory : public Data {
public:
    Memory();

    nlohmann::json to_json() override;

private:
    const uint64_t memory;
};


#endif //SYSTEM_INFO_MEMORY_HPP
