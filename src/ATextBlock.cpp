/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu]
** File description:
** ATextBlock
*/

#include "ATextBlock.hpp"

void acd::ATextBlock::setPosition(std::size_t line, std::size_t col)
{
    _line = line;
    _col = col;
}

std::pair<std::size_t, std::size_t> acd::ATextBlock::getPosition() const
{
    return {_line, _col};
}

void acd::ATextBlock::setText(const std::string &text)
{
    _text = text;
}

std::string acd::ATextBlock::getText() const
{
    return _text;
}

void acd::ATextBlock::setForeColor(Color color)
{
    _foreColor = color;
}

acd::Color acd::ATextBlock::getForeColor() const
{
    return _foreColor;
}

void acd::ATextBlock::setBackColor(Color color)
{
    _backColor = color;
}

acd::Color acd::ATextBlock::getBackColor() const
{
    return _backColor;
}
