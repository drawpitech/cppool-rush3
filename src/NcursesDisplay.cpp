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
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void NcursesDisplay::initialize()
{
}

void NcursesDisplay::update([[maybe_unused]] std::shared_ptr<OrchTable> data)
{
    clear();
    _windows.clear();
    int y_off = 0;
    for (const auto& [name, module] : *data) {
        WINDOW* win = subwin(stdscr, module->size() + 2, COLS, y_off, 0);
        _windows.push_back(win);
        y_off += module->size() + 2;
        int y_loff = 0;
        wcolor_set(win, 1, nullptr);
        box(win, 0, 0);
        mvwaddch(win, y_loff, 5 + name.size(), ACS_ULCORNER);
        mvwaddch(win, y_loff, 2, ACS_URCORNER);
        wcolor_set(win, 0, nullptr);
        wcolor_set(win, 2, nullptr);
        mvwprintw(win, y_loff++, 3, " %s ", name.c_str());
        wcolor_set(win, 0, nullptr);

        for (const auto& [key, value] : *module) {
            mvwprintw(win, y_loff, 3, "%s:", key.c_str());
            wcolor_set(win, 3, nullptr);
            mvwprintw(
                win, y_loff++, COLS - 3 - value->str().size(), "%s",
                value->str().c_str());
            wcolor_set(win, 0, nullptr);
        }
    }
}

void NcursesDisplay::render()
{
    for (const auto module : _windows) {
        wrefresh(module);
    }
    // refresh();
}

NcursesDisplay::~NcursesDisplay()
{
    endwin();
}
}
