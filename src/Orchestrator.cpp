/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Orchestrator.cpp
*/

#include "../include/Orchestrator.hpp"

namespace Krell {
void Orchestrator::addModule(const std::string& name,
                             std::unique_ptr<IModule> module) {
    _modules[name] = std::move(module);
}

void Orchestrator::update() {
    for (auto& [name, module] : _modules) {
        module->update();
    }
}
} // Krell
