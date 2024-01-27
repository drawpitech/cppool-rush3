/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** main.cpp
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <span>
#include <thread>

#include "modules/ProcessorModule.hpp"
#include "Args.hpp"
#include "Orchestrator.hpp"
#include "SFMLDisplay.hpp"
#include "IDisplay.hpp"
#include "modules/HostnameModule.hpp"
#include "modules/MemoryModule.hpp"
#include "modules/OSModule.hpp"
#include "modules/TimeModule.hpp"
#include "NCursesDisplay.hpp"

void displayHelp()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./myGKrellm" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tmyGKrellm is a system monitor." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    for (const auto& opt : OPTIONS) {
        std::cout << "\t";
        if (opt.c != '\0') {
            std::cout << "-" << opt.c << " ";
        }
        if (!opt.large.empty()) {
            std::cout << "--" << opt.large << " ";
        }
        std::cout << ": " << opt.description << "\n" << std::flush;
    }
}

void addModules(Krell::Orchestrator& orc)
{
    orc.addModule(std::make_unique<Krell::MemoryModule>());
    orc.addModule(std::make_unique<Krell::ProcessorModule>());
    orc.addModule(std::make_unique<Krell::OSModule>());
    orc.addModule(std::make_unique<Krell::HostnameModule>());
    orc.addModule(std::make_unique<Krell::TimeModule>());
}

std::unique_ptr<Krell::IDisplay> getDisplay(const options_t& options)
{
    std::clog << "Options: " << options << std::endl;
    if ((options & OPTS::DEBUG_MOD) != 0) {
        return nullptr;
    }
    if ((options & OPTS::GRAPHICAL) != 0) {
        return std::make_unique<Krell::SFMLDisplay>();
    }
    return std::make_unique<Krell::NCursesDisplay>();
}

int main(const int argc, const char* argv[])
{
    Krell::Orchestrator orchestrator;
    const auto interval = std::chrono::milliseconds(500);
    const options_t options = get_params(
        std::span{argv, static_cast<std::size_t>(argc)});

    if ((options & OPTS::HELP_MESS) != 0) {
        displayHelp();
        std::exit(0);
    }

    addModules(orchestrator);
    std::unique_ptr<Krell::IDisplay> display = getDisplay(options);

    while (display == nullptr || display->isRunning()) {
        orchestrator.update();

        if ((options & OPTS::DEBUG_MOD) != 0) {
            orchestrator.log();
        }

        if (display != nullptr) {
            display->update(orchestrator.getData());
            display->render();
        }

        std::this_thread::sleep_for(interval);
    }
}
