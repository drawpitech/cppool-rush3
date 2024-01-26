cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)

add_link_options(-fsanitize=address,undefined,leak)

add_compile_options(-Wall -Wextra -fsanitize=address,undefined,leak)

project(MyGKrellm CXX)

add_executable(MyGKrellm
        src/main.cpp
)

target_include_directories(MyGKrellm PUBLIC include)
