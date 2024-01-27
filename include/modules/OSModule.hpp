/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** OS.hpp
*/

#pragma once

#include <string>

#include "AModule.hpp"

namespace Krell {
class OSModule final : public AModule {
public:
    explicit OSModule(const std::string& file = "/proc/sys/kernel/hostname");

    void update() override;

    std::shared_ptr<ModuleTab> getData() const override;

    const std::string& getName() const override;

private:
    std::shared_ptr<ModuleTab> _data{new ModuleTab};

    static inline std::string _name{"OS"};
};
} // namespace Krell
