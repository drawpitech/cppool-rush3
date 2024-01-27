/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Orchestrator.cpp
*/


#include <iostream>
#include <ranges>
#include "Orchestrator.hpp"

namespace Krell {
void Orchestrator::addModule(
    std::unique_ptr<IModule> module) {
    _modules[module->getName()] = std::move(module);
}

void Orchestrator::update() {
    for (const auto& [name, module] : _modules) {
        module->update();
        (*_data)[name] = module->getData();
    }
}

void Orchestrator::log() const {
    for (const auto& [name, module] : _modules) {
        std::clog << "\nModule `" << name << "`:\n";
        module->log();
        std::clog << std::flush;
    }
}

std::shared_ptr<OrchTable> Orchestrator::getData() const {
    return _data;
}
} // Krell
