/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** main.cpp
*/

#include <iostream>
#include <span>
#include <modules/MemoryModule.hpp>

void displayHelp() {
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./myGKrellm" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tmyGKrellm is a system monitor." << std::endl;
}

[[noreturn]] int main(int argc, char* argv[]) {
    std::span args{argv, static_cast<std::size_t>(argc)};

    Krell::MemoryModule mem_module("/proc/meminfo");
    mem_module.update();

    mem_module.getData();

    for (auto& [key, value] : mem_module.getData()) {
        std::cout << key << ": " << value->toString() << std::endl;
    }

    while (true) {

    }

    // std::cout << mem_module.getModuleName() << std::endl;
}
