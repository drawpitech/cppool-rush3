/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Orchestrator.cpp
*/


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

std::shared_ptr<OrchTable> Orchestrator::getData() const {
    return _data;
}
} // Krell
