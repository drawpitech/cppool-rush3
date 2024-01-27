/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Orchestrator.cpp
*/


#include <ranges>
#include "Orchestrator.hpp"

namespace Krell {
void Orchestrator::addModule(const std::string& name,
                             std::unique_ptr<IModule> module) {
    _modules[name] = std::move(module);
}

void Orchestrator::update() {
    for (auto const &module: _modules | std::views::values) {
        module->update();
    }
}
} // Krell
