/*
** EPITECH PROJECT, 2023
** ArcadeShared [WSL: Ubuntu]
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

#include "TextBlock.hpp"

#include <iostream>
#include <ncurses.h>

acd::Ncurses::Ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    _initColors();
}

acd::Ncurses::~Ncurses()
{
    endwin();
}

void acd::Ncurses::getInputs()
{
    int ch = getch();
    std::map<int, acd::Input> dc = {
        {KEY_UP, acd::KEY__UP},
        {KEY_DOWN, acd::KEY__DOWN},
        {KEY_LEFT, acd::KEY__LEFT},
        {KEY_RIGHT, acd::KEY__RIGHT},
        {KEY_ENTER, acd::KEY__ENTER},
        {'\n', acd::KEY__ENTER},
        {27, acd::KEY__ESCAPE},
        {32, acd::KEY__SPACE},
        {97, acd::KEY__A},
        {98, acd::KEY__B},
        {99, acd::KEY__C},
        {100, acd::KEY__D},
        {101, acd::KEY__E},
        {102, acd::KEY__F},
        {103, acd::KEY__G},
        {104, acd::KEY__H},
        {105, acd::KEY__I},
        {106, acd::KEY__J},
        {107, acd::KEY__K},
        {108, acd::KEY__L},
        {109, acd::KEY__M},
        {110, acd::KEY__N},
        {111, acd::KEY__O},
        {112, acd::KEY__P},
        {113, acd::KEY__Q},
        {114, acd::KEY__R},
        {115, acd::KEY__S},
        {116, acd::KEY__T},
        {117, acd::KEY__U},
        {118, acd::KEY__V},
        {119, acd::KEY__W},
        {120, acd::KEY__X},
        {121, acd::KEY__Y},
        {122, acd::KEY__Z}
    };
    if (ch == ERR) {
        return;
    }
    if (dc.find(ch) != dc.end()) {
        addInput(dc.at(ch));
    }
}

void acd::Ncurses::display(GameMap const &map)
{
    std::pair<std::size_t, std::size_t> size = map.getSize();
    std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<acd::Block>> grid = map.getGrid();
    std::map<std::string, std::reference_wrapper<acd::TextBlock>> texts = map.getTexts();

    if ((int)size.second > COLS / 2 || (int)size.first > LINES) {
        erase();
        mvprintw(0, 0, "== Window is too small ==");
        mvprintw(2, 0, "Grid size %zu %zu", size.first, size.second);
        mvprintw(3, 0, "Window size %d %d", LINES, COLS);
        mvprintw(4, 0, "(eq to %d %d blocks)", LINES, COLS / 2);
        refresh();
        return;
    }
    erase();
    for (std::size_t y = 0; y < size.second; y++) {
        for (std::size_t x = 0; x < size.first; x++) {
            if (grid.find({x, y}) != grid.end()) {
                acd::Block &block = grid.at({x, y}).get();
                std::size_t posX = x;
                std::size_t posY = y;
                char *nchars = block.getCharactersNcurses();
                acd::Color foregroundColor = block.getForegroundColorNcurses();
                acd::Color backgroundColor = block.getBackgroundColorNcurses();

                _attrOnColors(foregroundColor, backgroundColor);
                mvaddch((int)posY, (int)posX * 2, nchars[0]);
                mvaddch((int)posY, (int)posX * 2 + 1, nchars[1]);
                _attrOffColors(foregroundColor, backgroundColor);
            }
        }
    }
    for (auto &text : texts) {
        std::pair<std::size_t, std::size_t> pos = text.second.get().getTextPosition();
        std::string str = text.second.get().getText();
        acd::Color foregroundColor = text.second.get().getColor();
        acd::Color backgroundColor = text.second.get().getBackColor();

        _attrOnColors(foregroundColor, backgroundColor);
        mvaddstr((int)pos.first, (int)pos.second * 2, str.c_str());
        _attrOffColors(foregroundColor, backgroundColor);
    }
    refresh();
}

void acd::Ncurses::_initColors()
{
    int color_pair_index = 1;
    std::array<acd::Color, 8> colors = {
        acd::Color::BLACK,
        acd::Color::RED,
        acd::Color::GREEN,
        acd::Color::YELLOW,
        acd::Color::BLUE,
        acd::Color::MAGENTA,
        acd::Color::CYAN,
        acd::Color::WHITE
    };
    std::array<acd::Color, 8> brightColors = {
        acd::Color::LIGHT_BLACK,
        acd::Color::LIGHT_RED,
        acd::Color::LIGHT_GREEN,
        acd::Color::LIGHT_YELLOW,
        acd::Color::LIGHT_BLUE,
        acd::Color::LIGHT_MAGENTA,
        acd::Color::LIGHT_CYAN,
        acd::Color::LIGHT_WHITE
    };

    for (int fg_color = 0; fg_color < 8; fg_color++) {
        for (int bg_color = 0; bg_color < 8; bg_color++) {
            init_pair(color_pair_index, fg_color, bg_color);
            _colorPairs[std::make_pair(colors[fg_color], colors[bg_color])] = std::make_pair(color_pair_index, false);
            _colorPairs[std::make_pair(brightColors[fg_color], colors[bg_color])] = std::make_pair(color_pair_index, true);
            _colorPairs[std::make_pair(colors[fg_color], brightColors[bg_color])] = std::make_pair(color_pair_index, false);
            _colorPairs[std::make_pair(brightColors[fg_color], brightColors[bg_color])] = std::make_pair(color_pair_index, true);
            color_pair_index++;
        }
    }
}

void acd::Ncurses::_attrOnColors(acd::Color foreColor, acd::Color backColor)
{
    std::pair<acd::Color, acd::Color> colors = std::make_pair(foreColor, backColor);

    if (_colorPairs.find(colors) != _colorPairs.end()) {
        std::pair<int, bool> colorPair = _colorPairs.at(colors);

        attron(COLOR_PAIR(colorPair.first));
        if (colorPair.second) {
            attron(A_BOLD);
        }
    }
}

void acd::Ncurses::_attrOffColors(acd::Color foreColor, acd::Color backColor)
{
    std::pair<acd::Color, acd::Color> colors = std::make_pair(foreColor, backColor);

    if (_colorPairs.find(colors) != _colorPairs.end()) {
        std::pair<int, bool> colorPair = _colorPairs.at(colors);

        attroff(COLOR_PAIR(colorPair.first));
        if (colorPair.second) {
            attroff(A_BOLD);
        }
    }
}
