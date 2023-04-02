/*
** EPITECH PROJECT, 2023
** ArcadeShared [WSL: Ubuntu]
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

#include "ATextBlock.hpp"

#include <iostream>

acd::Ncurses::Ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
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
        {27, acd::KEY_ESCAPE},
        {32, acd::KEY_SPACE},
        {97, acd::KEY_A},
        {98, acd::KEY_B},
        {99, acd::KEY_C},
        {100, acd::KEY_D},
        {101, acd::KEY_E},
        {102, acd::KEY_F},
        {103, acd::KEY_G},
        {104, acd::KEY_H},
        {105, acd::KEY_I},
        {106, acd::KEY_J},
        {107, acd::KEY_K},
        {108, acd::KEY_L},
        {109, acd::KEY_M},
        {110, acd::KEY_N},
        {111, acd::KEY_O},
        {112, acd::KEY_P},
        {113, acd::KEY_Q},
        {114, acd::KEY_R},
        {115, acd::KEY_S},
        {116, acd::KEY_T},
        {117, acd::KEY_U},
        {118, acd::KEY_V},
        {119, acd::KEY_W},
        {120, acd::KEY_X},
        {121, acd::KEY_Y},
        {122, acd::KEY_Z}
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
    std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<acd::IBlock>> grid = map.getGrid();
    std::map<std::string, std::reference_wrapper<acd::ITextBlock>> texts = map.getTexts();

    clear();
    for (std::size_t y = 0; y < size.second; y++) {
        for (std::size_t x = 0; x < size.first; x++) {
            if (grid.find({x, y}) != grid.end()) {
                acd::IBlock &block = grid.at({x, y}).get();
                std::size_t posX = x;
                std::size_t posY = y;
                char *nchars = block.getCharactersNcurses();

                mvprintw(posY, posX * 2, "%c%c", nchars[0], nchars[1]);
            }
        }
    }
    for (auto &text : texts) {
        std::pair<std::size_t, std::size_t> pos = text.second.get().getTextPosition();
        std::string str = text.second.get().getText();

        mvprintw((int)pos.second, (int)pos.first * 2, str.c_str());
    }
    timeout(50);
    refresh();
}

void acd::Ncurses::setRefBlocks(const std::map<std::string, std::reference_wrapper<acd::IBlock>> &refBlocks)
{
    _refBlocks = refBlocks;
}

const std::map<std::string, std::reference_wrapper<acd::IBlock>> &acd::Ncurses::getRefBlocks() const
{
    return _refBlocks;
}

acd::IBlock &acd::Ncurses::getRefBlock(const std::string &name) const
{
    return _refBlocks.at(name);
}
