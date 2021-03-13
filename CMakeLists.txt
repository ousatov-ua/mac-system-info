cmake_minimum_required(VERSION 3.17)
project(system_info)

include_directories(/usr/bin/include)

set(CMAKE_CXX_STANDARD 14)
find_package(nlohmann_json REQUIRED)
find_package(Curses REQUIRED)

find_library(iokit IOKit)

add_executable(system_info main.cpp core/util/System.cpp core/util/System.hpp
        core/SystemInfo.cpp core/SystemInfo.hpp
        core/types/Processor.cpp core/types/Processor.hpp
        core/types/types.hpp
        core/types/Memory.cpp core/types/Memory.hpp
        core/types/Data.cpp core/types/Data.hpp
        core/smc/smc.c core/smc/smc.h
        core/types/FansInfo.cpp core/types/FansInfo.hpp
        core/types/Gpu.cpp core/types/Gpu.hpp ui/console/UI.cpp ui/console/UI.hpp ui/console/Controller.cpp ui/console/Controller.hpp)
target_link_libraries(system_info nlohmann_json Curses "-framework IOKit")