//
// Created by alus on 08.03.2021.
//

#ifndef CPLUSPLUS_SYSTEMINFO_HPP
#define CPLUSPLUS_SYSTEMINFO_HPP

#include <_types/_uint64_t.h>
#include <string>
#include "types/Processor.hpp"
#include "types/Memory.hpp"

using namespace std;

class SystemInfo {
public:
    string to_string();

    SystemInfo();

    ~SystemInfo();

private:
    std::unique_ptr<Processor> const processor;
    std::unique_ptr<Memory> const memory;
};


#endif //CPLUSPLUS_SYSTEMINFO_HPP
