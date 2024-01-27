/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** ProcessorModule.hpp
*/

#pragma once

#include <string>

#include "AModule.hpp"

namespace Krell {
class ProcessorModule final : public AModule {
public:
    explicit ProcessorModule(std::string path = "/proc/cpuinfo");

    std::shared_ptr<ModuleTab> getData() const override;

    std::string const& getName() const override;

    void update() override;

    void subscribe(const std::string& name) override;

    void unsubscribe(const std::string& name) override;

private:
    std::shared_ptr<ModuleTab> _data{new ModuleTab};
    static inline const std::string _name{"processor"};
};
} // Krell
