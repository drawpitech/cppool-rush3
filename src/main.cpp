/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** main.cpp
*/

#include <iostream>
#include <thread>

#include "Args.hpp"
#include "Orchestrator.hpp"
#include "modules/MemoryModule.hpp"

void displayHelp() {
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./myGKrellm" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tmyGKrellm is a system monitor." << std::endl;
}

[[noreturn]] int main(const int argc, const char* argv[]) {
    options_t options = get_params(argc, argv);

    if (options & OPT_HELP_MESS) {
        displayHelp();
        exit(0);
    }

    Krell::Orchestrator orchestrator;

    const auto interval = std::chrono::seconds(1);

    orchestrator.addModule("memory",
                           std::make_unique<Krell::MemoryModule>());

    while (true) {
        std::this_thread::sleep_for(interval);

        orchestrator.update();
    }

    // std::cout << mem_module.getModuleName() << std::endl;
}


