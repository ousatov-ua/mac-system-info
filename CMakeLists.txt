cmake_minimum_required(VERSION 3.17)
project(system_info)

include_directories(/usr/bin/include)

set(CMAKE_CXX_STANDARD 14)
find_package(nlohmann_json REQUIRED)

find_library(iokit IOKit)

add_executable(system_info main.cpp util/System.cpp util/System.hpp
        SystemInfo.cpp SystemInfo.hpp
        types/Processor.cpp types/Processor.hpp
        common/types.hpp
        types/Memory.cpp types/Memory.hpp
        types/Data.cpp types/Data.hpp
        smc/smc.c smc/smc.h
        types/FansInfo.cpp types/FansInfo.hpp
        types/Gpu.cpp types/Gpu.hpp)
target_link_libraries(system_info nlohmann_json "-framework IOKit")