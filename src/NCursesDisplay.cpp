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
#include <vector>

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

void NCursesDisplay::handleInput()
{
    std::vector<std::string> win_names;
    win_names.reserve(_windows.size());
    for (const auto& [name, _] : _windows)
        win_names.push_back(name);

    switch (getch()) {
        case 'q':
            _running = false;
            break;
        case ' ':
            _windows[win_names[_selected]].folded =
                !_windows[win_names[_selected]].folded;
            break;
        case KEY_UP:
            _selected = _selected == 0 ? win_names.size() - 1 : _selected - 1;
            break;
        case KEY_DOWN:
            _selected = _selected >= win_names.size() - 1 ? 0 : _selected + 1;
            break;
        default:
            break;
    }
}

void NCursesDisplay::update(std::shared_ptr<OrchTable> data)
{
    handleInput();

    int y_off = 0;
    size_t i = 0;

    for (const auto& [name, module] : *data) {
        if (!_windows.contains(name))
            _windows[name] = {nullptr, false};

        Window& win = _windows[name];
        const bool is_selected = i == _selected;
        const int height = (win.folded) ? 2 : (int)module->size() + 2;

        if (win.win == nullptr) {
            win.win = subwin(stdscr, height, COLS, y_off, 0);
        } else {
            wclear(win.win);
            if (getbegy(win.win) != y_off) {
                delwin(win.win);
                win.win = subwin(stdscr, height, COLS, y_off, 0);
            }
            if (getmaxy(win.win) != height)
                wresize(win.win, height, COLS);
        }

        y_off += height;
        int y_loff = 0;

        wcolor_set(win.win, (is_selected) ? 2 : 1, nullptr);
        box(win.win, 0, 0);
        mvwaddch(win.win, y_loff, 2, ACS_URCORNER);
        mvwaddch(win.win, y_loff, 5 + name.size(), ACS_ULCORNER);
        wcolor_set(win.win, 0, nullptr);

        wcolor_set(win.win, 2, nullptr);
        mvwprintw(win.win, y_loff++, 3, " %s ", name.c_str());
        wcolor_set(win.win, 0, nullptr);

        if (!win.folded) {
            for (const auto& [key, value] : *module) {
                mvwprintw(win.win, y_loff, 3, "%s:", key.c_str());
                wcolor_set(win.win, 3, nullptr);
                mvwprintw(
                    win.win, y_loff++, (int)(COLS - 3 - value->str().size()),
                    "%s", value->str().c_str());
                wcolor_set(win.win, 0, nullptr);
            }
        }
        i++;
    }
}

void NCursesDisplay::render()
{
    for (const auto& [_, module] : _windows)
        wrefresh(module.win);
    refresh();
}

NCursesDisplay::~NCursesDisplay()
{
    for (const auto& [_, module] : _windows)
        delwin(module.win);
    endwin();
}
}  // namespace Krell
