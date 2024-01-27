/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Orchestrator.hpp
*/

#pragma once
#include <map>
#include <memory>
#include <string>

#include "IModule.hpp"

namespace Krell {
class Orchestrator {
public:
    Orchestrator() = default;

    void addModule(const std::string& name, std::unique_ptr<IModule> module);

    void update();

private:
    std::map<std::string, std::unique_ptr<IModule> > _modules{};
};
} // Krell
