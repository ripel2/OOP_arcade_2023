/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu]
** File description:
** ABlock
*/

#include "ABlock.hpp"

void acd::ABlock::setForeColor(Color color)
{
    _foreColor = color;
}

void acd::ABlock::setBackColor(Color color)
{
    _backColor = color;
}

acd::Color acd::ABlock::getForeColor() const
{
    return _foreColor;
}

acd::Color acd::ABlock::getBackColor() const
{
    return _backColor;
}

void acd::ABlock::setText(const char *text)
{
    _text = text;
}

const char *acd::ABlock::getText() const
{
    return _text;
}

void acd::ABlock::setTexturePath(const char *path)
{
    _texturePath = path;
}

const char *acd::ABlock::getTexturePath() const
{
    return _texturePath;
}
