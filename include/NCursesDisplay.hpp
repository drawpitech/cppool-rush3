/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** NcursesDisplay
*/

#pragma once

#include <ncurses.h>

#include <memory>

#include "IDisplay.hpp"
#include "Orchestrator.hpp"

namespace Krell {
class NCursesDisplay final : public IDisplay
{
   public:
    NCursesDisplay();

    bool isRunning() const override;

    void update(std::shared_ptr<OrchTable> data) override;

    void render() override;

    ~NCursesDisplay() override;

    struct Window
    {
        WINDOW* win;
        bool folded;
        bool exists;
    };

   private:
    std::map<std::string, Window> _windows;

    bool _running{true};
    size_t _selected{0};

    bool _menuOpen{false};
    WINDOW* _menu{nullptr};

    void handleInput();
};
}  // namespace Krell
