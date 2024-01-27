/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Memory.hpp
*/

#pragma once

#include <string>

#include "AModule.hpp"

namespace Krell {
class MemoryModule final : public AModule {
public:
    explicit MemoryModule(const std::string& file = "/proc/meminfo");

    void update() override;

    std::shared_ptr<ModuleTab> getData() const override;

    std::string const& getName() const override;

    void subscribe(std::string const& name) override;

    void unsubscribe(std::string const& name) override;

private:
    std::shared_ptr<ModuleTab> _data{new ModuleTab};
    static inline const std::string _name{"Memory"};
};
}
