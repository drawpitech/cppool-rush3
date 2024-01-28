/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** NCursesDisplay
*/

#include "NCursesDisplay.hpp"
#include "data/GraphData.hpp"

#include <ncurses.h>

#include <algorithm>
#include <array>
#include <memory>

namespace {
std::string getSelection(
    size_t selected,
    const std::map<std::string, Krell::NCursesDisplay::Window>& windows,
    bool exists = true)
{
    size_t i = 0;
    for (const auto& [name, module] : windows) {
        if (exists != module.exists)
            continue;
        if (i == selected)
            return name;
        i++;
    }
    return "";
}

size_t count_exists(
    const std::map<std::string, Krell::NCursesDisplay::Window>& windows)
{
    size_t count = 0;
    for (const auto& [_, module] : windows)
        if (module.exists)
            count += 1;
    return count;
}
} // namespace

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
    size_t count = (_menuOpen)
                       ? _windows.size() - count_exists(_windows)
                       : count_exists(_windows);
    std::string selection;

    switch (getch()) {
        case 'q':
            _running = false;
            break;

        case ' ':
            selection = getSelection(_selected, _windows, !_menuOpen);
            if (selection.empty())
                break;
            if (_menuOpen) {
                _windows[selection].exists = true;
                count -= 1;
            } else {
                _windows[selection].folded = !_windows[selection].folded;
            }
            break;

        case 'd':
            selection = getSelection(_selected, _windows);
            if (selection.empty())
                break;
            _windows[selection].exists = false;
            count -= 1;
            break;

        case KEY_UP:
            _selected = (_selected == 0) ? _selected : _selected - 1;
            break;

        case KEY_DOWN:
            _selected = (_selected >= count) ? count : _selected + 1;
            break;

        case 'a':
            _menuOpen = !_menuOpen;
            _selected = 0;
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
        const int height = (win.folded)
                               ? 2
                               : static_cast<int>(module->size()) * 2 + 2;

        if (win.win != nullptr)
            delwin(win.win);
        win.win = subwin(stdscr, height, COLS, y_off, 0);

        y_off += height;
        int y_loff = 0;

        wcolor_set(win.win, (!_menuOpen && is_selected) ? 2 : 1, nullptr);
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
                if (value->type() == Data::Graph) {
                    Data::GraphData<std::size_t>* graph = reinterpret_cast
                    <
                        Data::GraphData<std::size_t>*>(value.get());
                    int g_off = COLS - 4;
                    graph->size(COLS - 6);
                    for (const auto& val : graph->data()) {
                        const int val_h = (float)(val - graph->min()) /
                                          (graph->max() - graph->min()) * 4;
                        switch (val_h) {
                            case 0:
                                mvwaddch(win.win, y_loff, g_off--, '_');
                            break;
                            case 1:
                                mvwaddch(win.win, y_loff, g_off--, ACS_S9);
                                break;
                            case 2:
                                mvwaddch(win.win, y_loff, g_off--, ACS_S7);
                                break;
                            case 3:
                                mvwaddch(win.win, y_loff, g_off--, ACS_S3);
                                break;
                            case 4:
                                mvwaddch(win.win, y_loff, g_off--, ACS_S1);
                                break;
                        }
                    }
                }
                y_loff++;
            }
        }
        i++;
    }

    if (_menuOpen) {
        size_t count = _windows.size() - count_exists(_windows);

        if (_menu != nullptr)
            delwin(_menu);
        _menu = subwin(stdscr, count + 3 + int(count != 0), COLS - 6, 3, 3);
        wclear(_menu);
        box(_menu, 0, 0);
        mvwprintw(_menu, 1, 1, "  Press 'ENTER' on a module");
        int offset = 0;
        for (const auto& [name, module] : _windows) {
            if (module.exists)
                continue;
            const bool is_selected = size_t(offset) == _selected;

            if (is_selected)
                wcolor_set(_menu, 2, nullptr);
            mvwprintw(_menu, offset++ + 3, 1, "  %s", name.c_str());
            if (is_selected)
                wcolor_set(_menu, 0, nullptr);
        }
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
} // namespace Krellqq
