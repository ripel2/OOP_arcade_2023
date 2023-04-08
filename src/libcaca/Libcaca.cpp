/*
** EPITECH PROJECT, 2023
** ArcadeShared [WSL: Ubuntu]
** File description:
** Libcaca
*/

#include "Libcaca.hpp"

#include "TextBlock.hpp"

#include <iostream>

acd::Libcaca::Libcaca()
    : _canvas(caca_create_canvas(0, 0)), _display(caca_create_display(_canvas))
{

}

acd::Libcaca::~Libcaca()
{
    caca_free_display(_display);
    caca_free_canvas(_canvas);
}

void acd::Libcaca::getInputs()
{
    caca_event_t event = {};
    int ret = caca_get_event(_display, CACA_EVENT_KEY_PRESS, &event, 0);
    std::map<int, acd::Input> dc = {
        {CACA_KEY_UP, acd::KEY__UP},
        {CACA_KEY_DOWN, acd::KEY__DOWN},
        {CACA_KEY_LEFT, acd::KEY__LEFT},
        {CACA_KEY_RIGHT, acd::KEY__RIGHT},
        {CACA_KEY_RETURN, acd::KEY__ENTER},
        {CACA_KEY_ESCAPE, acd::KEY__ESCAPE},
        {' ', acd::KEY__SPACE},
        {'A', acd::KEY__A},
        {'B', acd::KEY__B},
        {'C', acd::KEY__C},
        {'D', acd::KEY__D},
        {'E', acd::KEY__E},
        {'F', acd::KEY__F},
        {'G', acd::KEY__G},
        {'H', acd::KEY__H},
        {'I', acd::KEY__I},
        {'J', acd::KEY__J},
        {'K', acd::KEY__K},
        {'L', acd::KEY__L},
        {'M', acd::KEY__M},
        {'N', acd::KEY__N},
        {'O', acd::KEY__O},
        {'P', acd::KEY__P},
        {'Q', acd::KEY__Q},
        {'R', acd::KEY__R},
        {'S', acd::KEY__S},
        {'T', acd::KEY__T},
        {'U', acd::KEY__U},
        {'V', acd::KEY__V},
        {'W', acd::KEY__W},
        {'X', acd::KEY__X},
        {'Y', acd::KEY__Y},
        {'Z', acd::KEY__Z}
    };

    if (ret == 0) {
        return;
    }
    if (dc.find(event.data.key.ch) != dc.end()) {
        addInput(dc.at(event.data.key.ch));
    }
    if (isalpha(event.data.key.ch) && dc.find(toupper(event.data.key.ch)) != dc.end()) {
        addInput(dc.at(toupper(event.data.key.ch)));
    }
}

void acd::Libcaca::display(GameMap const &map)
{
    std::pair<std::size_t, std::size_t> size = map.getSize();
    std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<acd::Block>> grid = map.getGrid();
    std::map<std::string, std::reference_wrapper<acd::TextBlock>> texts = map.getTexts();

    caca_set_canvas_size(_canvas, size.second, size.first);
    caca_clear_canvas(_canvas);
    for (std::size_t y = 0; y < size.second; y++) {
        for (std::size_t x = 0; x < size.first; x++) {
            if (grid.find({x, y}) != grid.end()) {
                acd::Block &block = grid.at({x, y}).get();
                std::size_t posX = x;
                std::size_t posY = y;
                char *nchars = block.getCharactersNcurses();
                acd::Color foregroundColor = block.getForegroundColorNcurses();
                acd::Color backgroundColor = block.getBackgroundColorNcurses();

                caca_set_color_ansi(_canvas, _convertColor(foregroundColor), _convertColor(backgroundColor));
                caca_put_char(_canvas, posX * 2, posY, nchars[0]);
                caca_put_char(_canvas, posX * 2 + 1, posY, nchars[1]);
                caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
            }
        }
    }
    for (auto &text : texts) {
        std::pair<std::size_t, std::size_t> pos = text.second.get().getTextPosition();
        std::string str = text.second.get().getText();
        acd::Color foregroundColor = text.second.get().getColor();
        acd::Color backgroundColor = text.second.get().getBackColor();

        caca_set_color_ansi(_canvas, _convertColor(foregroundColor), _convertColor(backgroundColor));
        caca_put_str(_canvas, pos.second * 2, pos.first, str.c_str());
        caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
    }
    caca_refresh_display(_display);
}

enum caca_color acd::Libcaca::_convertColor(acd::Color color)
{
    std::map<acd::Color, enum caca_color> color_map = {
        {acd::Color::BLACK, CACA_BLACK},
        {acd::Color::RED, CACA_RED},
        {acd::Color::GREEN, CACA_GREEN},
        {acd::Color::LIGHT_YELLOW, CACA_YELLOW},
        {acd::Color::YELLOW, CACA_YELLOW},
        {acd::Color::BLUE, CACA_BLUE},
        {acd::Color::MAGENTA, CACA_MAGENTA},
        {acd::Color::CYAN, CACA_CYAN},
        {acd::Color::WHITE, CACA_WHITE},
        {acd::Color::LIGHT_BLACK, CACA_LIGHTGRAY},
        {acd::Color::LIGHT_RED, CACA_LIGHTRED},
        {acd::Color::LIGHT_GREEN, CACA_LIGHTGREEN},
        {acd::Color::LIGHT_BLUE, CACA_LIGHTBLUE},
        {acd::Color::LIGHT_MAGENTA, CACA_LIGHTMAGENTA},
        {acd::Color::LIGHT_CYAN, CACA_LIGHTCYAN},
        {acd::Color::LIGHT_WHITE, CACA_WHITE}
    };
    
    auto it = color_map.find(color);
    if (it != color_map.end()) {
        return it->second;
    } else {
        return CACA_BLACK;
    }
}
