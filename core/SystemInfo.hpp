//
// Created by alus on 08.03.2021.
//

#ifndef CPLUSPLUS_SYSTEMINFO_HPP
#define CPLUSPLUS_SYSTEMINFO_HPP

#include <_types/_uint64_t.h>
#include <string>
#include "types/Processor.hpp"
#include "types/Memory.hpp"
#include "types/FansInfo.hpp"
#include "types/Gpu.hpp"

using namespace std;

class SystemInfo {
public:
    string toString();

    nlohmann::ordered_json toJson();

    SystemInfo();

    ~SystemInfo();

private:
    std::unique_ptr<Processor> const processor;
    std::unique_ptr<Memory> const memory;
    std::unique_ptr<FansInfo> const fans_info;
    std::unique_ptr<Gpu> const gpu;
};


#endif //CPLUSPLUS_SYSTEMINFO_HPP
