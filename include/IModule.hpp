/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** IModule.hpp
*/

#pragma once
#include "Data.hpp"

namespace Krell {
class IModule {
public:
    virtual ~IModule() = default;

    virtual void update() = 0;

    virtual std::shared_ptr<ModuleTab> getData() const = 0;

    virtual void subscribe(std::string const& name) = 0;

    virtual void unsubscribe(std::string const& name) = 0;

    virtual const std::string &getName() const = 0;
};
}
