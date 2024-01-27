/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** NcursesDisplay
*/

#pragma once

#include <ncurses.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "IDisplay.hpp"

namespace Krell {
class NcursesDisplay final : public IDisplay
{
public:
    NcursesDisplay();

    void initialize() override;

    void update(std::shared_ptr<OrchTable> data) override;

    void render() const override;

    ~NcursesDisplay() override;

private:
    std::vector<WINDOW*> _windows;
};
}
