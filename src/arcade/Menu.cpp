/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"

acd::Menu::Menu()
    : _selectedGameLibPath(""), _selectedGraphicLibPath(""),
    _selectedGraphicLibIndex(0), _selectedGameLibIndex(0), _usernameCursorIndex(0),
    _selectedGraphicLib(false), _selectedGameLib(false), _typedUsername(false), _map(32, 24)
{
    for (std::size_t i = 0; i < 10; i++)
        _username[i] = ' ';
    _username[10] = '\0';
    _initTitleBlocks();
    _initOptionBlocks();
    setMap(_map);
}

void acd::Menu::_initTitleBlocks()
{
    char logo[5][32] = {
        "  XXX  XXX  XXX  XXX  XX   XXX ",
        "  X X  X X  X    X X  X X  X   ",
        "  XXX  XX   X    XXX  X X  XXX ",
        "  X X  X X  X    X X  X X  X   ",
        "  X X  X X  XXX  X X  XX   XXX "
    };
    std::unique_ptr<Block> logoBlock = std::make_unique<Block>();
    char blockchars[2] = {' ', ' '};
    logoBlock.get()->loadTexturesNcurses(Color::WHITE, Color::BLUE, blockchars);
    _blocks.push_back(std::move(logoBlock));
    for (std::size_t y = 0; y < 5; y++) {
        for (std::size_t x = 0; x < 32; x++) {
            if (logo[y][x] == 'X')
                _map.setBlock(x, y + 2, *_blocks[0].get());
        }
    }
}

void acd::Menu::_initOptionBlocks()
{
    std::unique_ptr<TextBlock> titleBlock = std::make_unique<TextBlock>();
    titleBlock.get()->setText("Choose a graphic library:");
    titleBlock.get()->setTextPosition(8, 2);
    titleBlock.get()->setBackColor(Color::BLACK);
    titleBlock.get()->setColor(Color::WHITE);
    _map.setText("titleBlock", *titleBlock.get());
    _textBlocks.push_back(std::move(titleBlock));
    for (std::size_t c = 0; c < 13; c++) {
        std::unique_ptr<TextBlock> block = std::make_unique<TextBlock>();
        block.get()->setTextPosition(10 + c, 2);
        block.get()->setBackColor(Color::BLACK);
        block.get()->setColor(Color::WHITE);
        _map.setText("optionBlock" + std::to_string(c), *block.get());
        _textBlocks.push_back(std::move(block));
    }
}

void acd::Menu::_initUsernameChars()
{
    for (std::size_t c = 0; c < 13; c++) {
        _map.removeText("optionBlock" + std::to_string(c));
    }
    for (std::size_t c = 0; c < sizeof(_username) - 1; c++) {
        std::unique_ptr<TextBlock> block = std::make_unique<TextBlock>();
        block.get()->setTextPosition(10, 2 + c);
        block.get()->setBackColor(Color::BLACK);
        block.get()->setColor(Color::WHITE);
        _map.setText("usernameChar" + std::to_string(c), *block.get());
        _textBlocks.push_back(std::move(block));
    }
}

void acd::Menu::setAvailableGraphicLibs(const std::vector<std::string> &libs)
{
    _availableGraphicLibs = libs;
}

void acd::Menu::setAvailableGameLibs(const std::vector<std::string> &libs)
{
    _availableGameLibs = libs;
}

void acd::Menu::arrowUp()
{
    if (_selectedGraphicLib && _selectedGameLib)
        return;
    std::size_t &cursor = !_selectedGraphicLib ? _selectedGraphicLibIndex : _selectedGameLibIndex;
    std::vector<std::string> &libs = !_selectedGraphicLib ? _availableGraphicLibs : _availableGameLibs;

    if (cursor == 0)
        cursor = libs.size() - 1;
    else
        cursor--;
}

void acd::Menu::arrowDown()
{
    if (_selectedGraphicLib && _selectedGameLib)
        return;
    std::size_t &cursor = !_selectedGraphicLib ? _selectedGraphicLibIndex : _selectedGameLibIndex;
    std::vector<std::string> &libs = !_selectedGraphicLib ? _availableGraphicLibs : _availableGameLibs;

    if (cursor == libs.size() - 1)
        cursor = 0;
    else
        cursor++;
}

void acd::Menu::arrowLeft()
{
    if (!_selectedGraphicLib || !_selectedGameLib)
        return;
    if (_usernameCursorIndex == 0)
        _usernameCursorIndex = sizeof(_username) - 2;
    else
        _usernameCursorIndex--;
}

void acd::Menu::arrowRight()
{
    if (!_selectedGraphicLib || !_selectedGameLib)
        return;
    if (_usernameCursorIndex == sizeof(_username) - 2)
        _usernameCursorIndex = 0;
    else
        _usernameCursorIndex++;
}

void acd::Menu::addCharToUsername(acd::Input latestInput)
{
    if (!_selectedGraphicLib || !_selectedGameLib)
        return;
    std::map<acd::Input, char> dc = {
        { acd::Input::KEY__A, 'A' },
        { acd::Input::KEY__B, 'B' },
        { acd::Input::KEY__C, 'C' },
        { acd::Input::KEY__D, 'D' },
        { acd::Input::KEY__E, 'E' },
        { acd::Input::KEY__F, 'F' },
        { acd::Input::KEY__G, 'G' },
        { acd::Input::KEY__H, 'H' },
        { acd::Input::KEY__I, 'I' },
        { acd::Input::KEY__J, 'J' },
        { acd::Input::KEY__K, 'K' },
        { acd::Input::KEY__L, 'L' },
        { acd::Input::KEY__M, 'M' },
        { acd::Input::KEY__N, 'N' },
        { acd::Input::KEY__O, 'O' },
        { acd::Input::KEY__P, 'P' },
        { acd::Input::KEY__Q, 'Q' },
        { acd::Input::KEY__R, 'R' },
        { acd::Input::KEY__S, 'S' },
        { acd::Input::KEY__T, 'T' },
        { acd::Input::KEY__U, 'U' },
        { acd::Input::KEY__V, 'V' },
        { acd::Input::KEY__W, 'W' },
        { acd::Input::KEY__X, 'X' },
        { acd::Input::KEY__Y, 'Y' },
        { acd::Input::KEY__Z, 'Z' },
        { acd::Input::KEY__SPACE, ' '}
    };

    if (dc.find(latestInput) == dc.end())
        return;
    _username[_usernameCursorIndex] = dc[latestInput];
}

void acd::Menu::pressEnter()
{
    if (!_selectedGraphicLib) {
        _selectedGraphicLib = true;
        _selectedGraphicLibPath = _availableGraphicLibs[_selectedGraphicLibIndex];
        _map.getText("titleBlock").setText("Choose a game library:");
    } else if (!_selectedGameLib) {
        _selectedGameLib = true;
        _selectedGameLibPath = _availableGameLibs[_selectedGameLibIndex];
        _map.getText("titleBlock").setText("Enter your username:");
        _initUsernameChars();
    } else if (!_typedUsername) {
        _typedUsername = true;
    }
}

void acd::Menu::updateMap()
{
    std::vector<std::string> &libs = !_selectedGraphicLib ? _availableGraphicLibs : _availableGameLibs;
    std::size_t &cursor = !_selectedGraphicLib ? _selectedGraphicLibIndex : _selectedGameLibIndex;

    if (!_selectedGraphicLib || !_selectedGameLib) {
        for (std::size_t c = 0; c < 13; c++) {
            if (c == cursor) {
                _map.getText("optionBlock" + std::to_string(c)).setColor(Color::BLACK);
                _map.getText("optionBlock" + std::to_string(c)).setBackColor(Color::WHITE);
            } else {
                _map.getText("optionBlock" + std::to_string(c)).setColor(Color::WHITE);
                _map.getText("optionBlock" + std::to_string(c)).setBackColor(Color::BLACK);
            }
            if (c < libs.size())
                _map.getText("optionBlock" + std::to_string(c)).setText(libs[c]);
            else
                _map.getText("optionBlock" + std::to_string(c)).setText("");
        }
    } else {
        for (std::size_t c = 0; c < sizeof(_username) - 1; c++) {
            if (c == _usernameCursorIndex) {
                _map.getText("usernameChar" + std::to_string(c)).setColor(Color::BLACK);
                _map.getText("usernameChar" + std::to_string(c)).setBackColor(Color::WHITE);
            } else {
                _map.getText("usernameChar" + std::to_string(c)).setColor(Color::WHITE);
                _map.getText("usernameChar" + std::to_string(c)).setBackColor(Color::BLACK);
            }
            _map.getText("usernameChar" + std::to_string(c)).setText(std::string(1, _username[c] == ' ' ? '_' : _username[c]));
        }
    }
    setMap(_map);
}

acd::updateType_t acd::Menu::update(acd::Input latestInput)
{
    switch (latestInput) {
        case acd::Input::KEY__UP:
            arrowUp();
            break;
        case acd::Input::KEY__DOWN:
            arrowDown();
            break;
        case acd::Input::KEY__LEFT:
            arrowLeft();
            break;
        case acd::Input::KEY__RIGHT:
            arrowRight();
            break;
        case acd::Input::KEY__ENTER:
            pressEnter();
            break;
        case acd::Input::KEY__A:
        case acd::Input::KEY__B:
        case acd::Input::KEY__C:
        case acd::Input::KEY__D:
        case acd::Input::KEY__E:
        case acd::Input::KEY__F:
        case acd::Input::KEY__G:
        case acd::Input::KEY__H:
        case acd::Input::KEY__I:
        case acd::Input::KEY__J:
        case acd::Input::KEY__K:
        case acd::Input::KEY__L:
        case acd::Input::KEY__M:
        case acd::Input::KEY__N:
        case acd::Input::KEY__O:
        case acd::Input::KEY__P:
        case acd::Input::KEY__Q:
        case acd::Input::KEY__R:
        case acd::Input::KEY__S:
        case acd::Input::KEY__T:
        case acd::Input::KEY__U:
        case acd::Input::KEY__V:
        case acd::Input::KEY__W:
        case acd::Input::KEY__X:
        case acd::Input::KEY__Y:
        case acd::Input::KEY__Z:
        case acd::Input::KEY__SPACE:
            addCharToUsername(latestInput);
        default:
            break;
    }
    updateMap();
    return acd::updateType_t::UPDATE_NONE;
}
