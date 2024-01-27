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
    explicit MemoryModule(const std::string& file);

    void update() override;

    DataTab &getData() override;

private:
    DataTab _data;
};
}
