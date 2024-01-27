cmake_minimum_required(VERSION 3.27)

project(MyGKrellm CXX)

set(CMAKE_CXX_STANDARD 20)
add_link_options(-fsanitize=address,undefined,leak)
add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined,leak)

add_executable(MyGKrellm
        src/main.cpp
        src/modules/MemoryModule.cpp
        src/AModule.cpp
        src/Data.cpp
        src/Orchestrator.cpp
        include/Orchestrator.hpp
        src/modules/ProcessorModule.cpp
        include/modules/ProcessorModule.hpp
)

target_include_directories(MyGKrellm PUBLIC include)
find_package(GTest CONFIG REQUIRED)
