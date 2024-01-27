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
using OrchTable = std::map<std::string, std::shared_ptr<ModuleTab> >;

class Orchestrator {
public:
    Orchestrator() = default;

    void addModule(std::unique_ptr<IModule> module);

    void update();
    void log() const;

    std::shared_ptr<OrchTable> getData() const;

private:
    std::map<std::string, std::unique_ptr<IModule> > _modules{};

    std::shared_ptr<OrchTable> _data{new OrchTable};
};
} // Krell
