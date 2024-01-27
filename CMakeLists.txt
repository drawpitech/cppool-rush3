cmake_minimum_required(VERSION 3.27)

project(MyGKrellm CXX)

set(CMAKE_CXX_STANDARD 20)
add_link_options(-fsanitize=address,undefined,leak -g)
add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined,leak -g)

add_executable(MyGKrellm
        src/main.cpp
        src/modules/MemoryModule.cpp
        src/AModule.cpp
        src/Data.cpp
        src/Orchestrator.cpp
        src/modules/ProcessorModule.cpp
        src/modules/HostnameModule.cpp
        src/modules/OSModule.cpp
        src/Args.cpp
)

target_include_directories(MyGKrellm PUBLIC include)
find_package(GTest CONFIG REQUIRED)
