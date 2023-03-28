/*
** EPITECH PROJECT, 2023
** arcadedev
** File description:
** sfml
*/

#include "sfml.hpp"


acd::sfml::sfml()
{
    _window.create(sf::VideoMode(800, 600), "Arcade");
}

acd::sfml::~sfml()
{
    _window.close();
}

void acd::sfml::setGridSize(std::size_t lines, std::size_t cols)
{
    _blocks.resize(lines);
    for (auto &line : _blocks)
        line.resize(cols);
}

std::pair<std::size_t, std::size_t> acd::sfml::getGridSize() const
{
    return std::make_pair(0, 0);
}

std::vector<std::vector<std::reference_wrapper<Block>>> & acd::sfml::getBlocks()
{
    return _blocks;
}

void acd::sfml::clearBlocks()
{

}

void acd::sfml::removeBlocks()
{
    _blocks.clear();
}

void acd::sfml::setBlock(std::size_t line, std::size_t col, Block &block)
{
    _blocks[line][col] = block;
}

Block & acd::sfml::getBlock(std::size_t line, std::size_t col)
{
    return _blocks[line][col];
}

void clearBlock(std::size_t line, std::size_t col)
{
    _blocks[line][col] = Block();
}

void addTextBlock(std::size_t line, std::size_t col, std::string text)
{

}

TextBlock &getTextBlock(const std::string &name)
{

}

void removeTextBlock(const std::string &name)
{

}

void removeTextBlock(const std::string &name)
{

}

void removeTextBlocks()
{

}

void acd::sfml::display()
{
    _window.display();
}

acd::Input acd::sfml::getInput()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up ? _input = KEY_UP : NONE);
            else if (event.key.code == sf::Keyboard::Down ? _input = KEY_DOWN : NONE);
            else if (event.key.code == sf::Keyboard::Left ? _input = KEY_LEFT : NONE);
            else if (event.key.code == sf::Keyboard::Right ? _input = KEY_RIGHT : NONE);
            else if ( event.key.code == sf::Keyboard::Return ? _input = KEY_ENTER : NONE);
            else if (event.key.code == sf::Keyboard::Escape ? _input = KEY_ESCAPE : NONE);
            else if (event.key.code == sf::Keyboard::Space ? _input = KEY_SPACE : NONE);
            else if (event.key.code == sf::Keyboard::A ? _input = KEY_A : NONE);
            else if (event.key.code == sf::Keyboard::B ? _input = KEY_B : NONE);
            else if (event.key.code == sf::Keyboard::C ? _input = KEY_C : NONE);
            else if (event.key.code == sf::Keyboard::D ? _input = KEY_D : NONE);
            else if (event.key.code == sf::Keyboard::E ? _input = KEY_E : NONE);
            else if (event.key.code == sf::Keyboard::F ? _input = KEY_F : NONE);
            else if (event.key.code == sf::Keyboard::G ? _input = KEY_G : NONE);
            else if (event.key.code == sf::Keyboard::H ? _input = KEY_H : NONE);
            else if (event.key.code == sf::Keyboard::I ? _input = KEY_I : NONE);
            else if (event.key.code == sf::Keyboard::J ? _input = KEY_J : NONE);
            else if (event.key.code == sf::Keyboard::K ? _input = KEY_K : NONE);
            else if (event.key.code == sf::Keyboard::L ? _input = KEY_L : NONE);
            else if (event.key.code == sf::Keyboard::M ? _input = KEY_M : NONE);
            else if (event.key.code == sf::Keyboard::N ? _input = KEY_N : NONE);
            else if (event.key.code == sf::Keyboard::O ? _input = KEY_O : NONE);
            else if (event.key.code == sf::Keyboard::P ? _input = KEY_P : NONE);
            else if (event.key.code == sf::Keyboard::Q ? _input = KEY_Q : NONE);
            else if (event.key.code == sf::Keyboard::R ? _input = KEY_R : NONE);
            else if (event.key.code == sf::Keyboard::S ? _input = KEY_S : NONE);
            else if (event.key.code == sf::Keyboard::T ? _input = KEY_T : NONE);
            else if (event.key.code == sf::Keyboard::U ? _input = KEY_U : NONE);
            else if (event.key.code == sf::Keyboard::V ? _input = KEY_V : NONE);
            else if (event.key.code == sf::Keyboard::W ? _input = KEY_W : NONE);
            else if (event.key.code == sf::Keyboard::X ? _input = KEY_X : NONE);
            else if (event.key.code == sf::Keyboard::Y ? _input = KEY_Y : NONE);
            else if (event.key.code == sf::Keyboard::Z ? _input = KEY_Z : NONE);
            else _input = NONE;
        }
    }
}

acd::Input acd::sfml::getLatestKeyboardInput() const
{
    return _input;
}


