/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** ProcessorModule.hpp
*/

#pragma once

#include "AModule.hpp"

namespace Krell {
class ProcessorModule : public AModule {
public:
    explicit ProcessorModule(const std::string& path = "/proc/cpuinfo");

    DataTab& getData() override;

    void update() override;

    void subscribe(const std::string& name) override;

    void unsubscribe(const std::string& name) override;

private:
    DataTab _data;
};
} // Krell
