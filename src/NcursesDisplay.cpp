/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** NcursesDisplay
*/

#include <ncurses.h>
#include <memory>

#include "Orchestrator.hpp"
#include "NcursesDisplay.hpp"

namespace Krell {
NcursesDisplay::NcursesDisplay()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

void NcursesDisplay::initialize()
{
}

void NcursesDisplay::update([[maybe_unused]] std::shared_ptr<OrchTable> data)
{
    // clear();
    _windows.clear();
    int y = 0;
    for (const auto& [name, module] : *data) {
        WINDOW* win = subwin(stdscr, 10, 40, y, 0);
        _windows.push_back(win);
        y += 10;
        box(win, 0, 0);
        mvwprintw(win, 0, 2, name.c_str());
    }
}

void NcursesDisplay::render() const
{
    for (const auto module: _windows) {
        wrefresh(module);
    }
    // refresh();
}

NcursesDisplay::~NcursesDisplay()
{
    endwin();
}
}
