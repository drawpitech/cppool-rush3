/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Orchestrator.hpp
*/

#pragma once
#include <IModule.hpp>
#include <map>
#include <memory>
#include <string>

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
