//
// Created by alus on 09.03.2021.
//

#ifndef SYSTEM_INFO_FANSINFO_HPP
#define SYSTEM_INFO_FANSINFO_HPP


#include <memory>
#include "../smc/smc.h"
#include "Data.hpp"

class FansInfo : public Data {
public:
    Fan_info fans_info{};

    void update();

    nlohmann::json toJson() override;
};


#endif //SYSTEM_INFO_FANSINFO_HPP
