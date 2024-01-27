/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** main.cpp
*/

#include <iostream>
#include <memory>
#include <thread>

#include "Args.hpp"
#include "NcursesDisplay.hpp"
#include "Orchestrator.hpp"
#include "modules/HostnameModule.hpp"
#include "modules/MemoryModule.hpp"
#include "modules/OSModule.hpp"
#include "modules/ProcessorModule.hpp"
#include "modules/TimeModule.hpp"

void displayHelp()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./myGKrellm" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tmyGKrellm is a system monitor." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    for (const auto& opt : OPTIONS) {
        std::cout << "\t";
        if (opt.c != '\0')
            std::cout << "-" << opt.c << " ";
        if (!opt.large.empty())
            std::cout << "--" << opt.large << " ";
        std::cout << ": " << opt.description << "\n" << std::flush;
    }
}

void addModules(Krell::Orchestrator& orc)
{
    // orc.addModule(std::make_unique<Krell::MemoryModule>());
    orc.addModule(std::make_unique<Krell::ProcessorModule>());
    orc.addModule(std::make_unique<Krell::OSModule>());
    orc.addModule(std::make_unique<Krell::HostnameModule>());
    orc.addModule(std::make_unique<Krell::TimeModule>());
}

std::unique_ptr<Krell::IDisplay> getDisplay(const options_t& options)
{
    std::clog << "Options: " << options << std::endl;
    if ((options & OPTS::DEBUG_MOD) != 0)
        return nullptr;
    return std::make_unique<Krell::NcursesDisplay>();
}

[[noreturn]] int main(const int argc, const char* argv[])
{
    const options_t options = get_params(argc, argv);

    if ((options & OPTS::HELP_MESS) != 0) {
        displayHelp();
        std::exit(0);
    }

    Krell::Orchestrator orchestrator;
    const auto interval = std::chrono::seconds(1);

    addModules(orchestrator);

    std::unique_ptr<Krell::IDisplay> display = getDisplay(options);

    while (true) {
        orchestrator.update();
        if ((options & OPTS::DEBUG_MOD) != 0)
            orchestrator.log();

        if (display != nullptr) {
            display->update(orchestrator.getData());
            display->render();
        }

        std::this_thread::sleep_for(interval);
    }
}
