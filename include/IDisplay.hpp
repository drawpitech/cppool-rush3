/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** IDisplay.hpp
*/

#pragma once
#include <Orchestrator.hpp>
#include <memory>

namespace Krell {
class IDisplay {
public:
    virtual ~IDisplay() = default;

    virtual void initialize() = 0;

    virtual void update(std::shared_ptr<OrchTable> data) = 0;

    virtual void render() = 0;
};
} // Krell
