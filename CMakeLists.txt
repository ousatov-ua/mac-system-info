cmake_minimum_required(VERSION 3.17)
project(system_info)

include_directories(/usr/bin/include)

set(CMAKE_CXX_STANDARD 14)
find_package(nlohmann_json REQUIRED)

find_library(iokit IOKit)

add_executable(system_info main.cpp system/util/System.cpp system/util/System.hpp
        system/SystemInfo.cpp system/SystemInfo.hpp
        system/types/Processor.cpp system/types/Processor.hpp
        system/types/types.hpp
        system/types/Memory.cpp system/types/Memory.hpp
        system/types/Data.cpp system/types/Data.hpp
        system/smc/smc.c system/smc/smc.h
        system/types/FansInfo.cpp system/types/FansInfo.hpp
        system/types/Gpu.cpp system/types/Gpu.hpp ui/console/UI.cpp ui/console/UI.hpp ui/console/Controller.cpp ui/console/Controller.hpp)
target_link_libraries(system_info nlohmann_json "-framework IOKit")