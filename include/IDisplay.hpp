/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** IDisplay.hpp
*/

#pragma once
#include <memory>

#include "Orchestrator.hpp"

namespace Krell {
class IDisplay
{
public:
    virtual ~IDisplay() = default;

    virtual bool isRunning() const = 0;

    virtual void update(std::shared_ptr<OrchTable> data) = 0;

    virtual void render() = 0;
};
} // Krell
