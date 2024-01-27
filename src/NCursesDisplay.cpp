/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** NCursesDisplay
*/

#include "NCursesDisplay.hpp"

#include <ncurses.h>

#include <algorithm>
#include <memory>

#include "Orchestrator.hpp"

namespace Krell {
NCursesDisplay::NCursesDisplay()
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

bool NCursesDisplay::isRunning() const
{
    return _running;
}

void NCursesDisplay::handleInput(std::vector<std::string> windows)
{
    switch (getch()) {
        case 'q':
            _running = false;
            break;
        case ' ':
            if (_folded.find(windows.at(_selected)) != _folded.end()) {
                _folded.erase(windows.at(_selected));
            } else {
                _folded.insert(windows.at(_selected));
            }
            break;
        case KEY_UP:
            _selected = _selected == 0 ? windows.size() - 1 : _selected - 1;
            break;
        case KEY_DOWN:
            _selected = _selected >= windows.size() - 1 ? 0 : _selected + 1;
            break;
        default:
            break;
    }
}

void NCursesDisplay::update(std::shared_ptr<OrchTable> data)
{
    clear();
    _windows.clear();

    std::vector<std::string> windows;
    for (const auto& [name, _] : *data)
        windows.push_back(name);
    handleInput(windows);

    int y_off = 0;
    size_t i = 0;
    for (const auto& [name, module] : *data) {
        const bool is_folded = _folded.find(name) != _folded.end();
        const bool is_selected = i == _selected;
        const int height = (is_folded) ? 2 : module->size() + 2;

        WINDOW* win = subwin(stdscr, height, COLS, y_off, 0);
        _windows.push_back(win);
        y_off += height;
        int y_loff = 0;
        wcolor_set(win, 1, nullptr);

        if (is_selected)
            wcolor_set(win, 2, nullptr);
        box(win, 0, 0);
        mvwaddch(win, y_loff, 5 + name.size(), ACS_ULCORNER);
        mvwaddch(win, y_loff, 2, ACS_URCORNER);
        if (is_selected)
            wcolor_set(win, 0, nullptr);

        wcolor_set(win, 0, nullptr);
        wcolor_set(win, 2, nullptr);
        mvwprintw(win, y_loff++, 3, " %s ", name.c_str());
        wcolor_set(win, 0, nullptr);

        if (!is_folded) {
            for (const auto& [key, value] : *module) {
                mvwprintw(win, y_loff, 3, "%s:", key.c_str());
                wcolor_set(win, 3, nullptr);
                mvwprintw(
                    win, y_loff++, COLS - 3 - value->str().size(), "%s",
                    value->str().c_str());
                wcolor_set(win, 0, nullptr);
            }
        }
        i++;
    }
}

void NCursesDisplay::render()
{
    for (const auto module : _windows) {
        wrefresh(module);
    }
    // refresh();
}

NCursesDisplay::~NCursesDisplay()
{
    endwin();
}
}  // namespace Krell
