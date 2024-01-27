/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** main.cpp
*/

#include <iostream>
#include <thread>

#include "modules/ProcessorModule.hpp"
#include "Args.hpp"
#include "Orchestrator.hpp"
#include "modules/HostnameModule.hpp"
#include "modules/MemoryModule.hpp"
#include "modules/OSModule.hpp"

void displayHelp() {
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./myGKrellm" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tmyGKrellm is a system monitor." << std::endl;
}

void addModules(Krell::Orchestrator& orc) {
    orc.addModule(std::make_unique<Krell::MemoryModule>());
    orc.addModule(std::make_unique<Krell::ProcessorModule>());
    orc.addModule(std::make_unique<Krell::OSModule>());
    orc.addModule(std::make_unique<Krell::HostnameModule>());
}

[[noreturn]] int main(const int argc, const char* argv[]) {
    options_t options = get_params(argc, argv);

    if ((options & OPT_HELP_MESS) != 0) {
        displayHelp();
        exit(0);
    }

    Krell::Orchestrator orchestrator;
    const auto interval = std::chrono::seconds(1);

    addModules(orchestrator);

    while (true) {
        orchestrator.update();
        auto data = orchestrator.getData();
        std::this_thread::sleep_for(interval);
    }
}
