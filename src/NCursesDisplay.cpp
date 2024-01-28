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

namespace {
std::string getSelection(
    size_t selected,
    const std::map<std::string, Krell::NCursesDisplay::Window>& windows)
{
    size_t i = 0;
    for (const auto& [name, module] : windows) {
        if (!module.exists)
            continue;
        if (i == selected)
            return name;
        i++;
    }
    return "";
}
}  // namespace

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
    size_t count = 0;
    for (const auto& [_, module] : _windows)
        if (module.exists)
            count += 1;
    if (count != 0)
        count -= 1;
    std::string selection;

    switch (getch()) {
        case 'q':
            _running = false;
            break;
        case ' ':
            selection = getSelection(_selected, _windows);
            if (!selection.empty())
                _windows[selection].folded = !_windows[selection].folded;
            break;
        case 'd':
            selection = getSelection(_selected, _windows);
            if (selection.empty())
                break;
            _windows[selection].exists = false;
            if (_selected >= count)
                _selected = count - 1;
            break;
        case KEY_UP:
            _selected = (_selected == 0) ? _selected : _selected - 1;
            break;
        case KEY_DOWN:
            _selected = (_selected >= count) ? count : _selected + 1;
            break;
        default:
            break;
    }
    std::clamp(_selected, size_t(0), count);
}

void NCursesDisplay::update(std::shared_ptr<OrchTable> data)
{
    handleInput();

    int y_off = 0;
    size_t i = 0;

    clear();
    for (const auto& [name, module] : *data) {
        if (!_windows.contains(name))
            _windows[name] = {nullptr, false, true};

        Window& win = _windows[name];
        if (!win.exists)
            continue;
        const bool is_selected = i == _selected;
        const int height = (win.folded) ? 2 : (int)module->size() + 2;

        if (win.win != nullptr)
            delwin(win.win);
        win.win = subwin(stdscr, height, COLS, y_off, 0);

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
