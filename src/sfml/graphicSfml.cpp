/*
** EPITECH PROJECT, 2023
** arcadedevparty
** File description:
** graphicSfml
*/

#include "graphicSfml.hpp"

acd::graphicSfml::graphicSfml()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade");
    _createRefBlocks();
}

acd::graphicSfml::~graphicSfml()
{

    _window.close();
}

void acd::graphicSfml::display(GameMap const &map)
{
    std::pair<std::size_t, std::size_t> size = map.getSize();
    std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<acd::IBlock>> grid = map.getGrid();
    std::map<std::string, std::reference_wrapper<acd::ITextBlock>> texts = map.getTexts();
    sf::Sprite foreground = sf::Sprite();
    sf::Texture foregroundText = sf::Texture();
    sf::Sprite background = sf::Sprite();
    sf::Texture backgroundText = sf::Texture();

    _window.clear();
    for (std::size_t y = 0; y < size.first; y++) {
        for (std::size_t x = 0; x < size.second; x++) {
            if (grid.find({x, y}) != grid.end()) {
                acd::IBlock &block = grid.at({x, y}).get();
                std::size_t posX = x;
                std::size_t posY = y;
                backgroundText.loadFromFile(block.getBackground());
                background.setTexture(backgroundText);
                background.setPosition(posX * 32, posY * 32);
                background.setScale(0.5, 0.5);
                _window.draw(background);
                if (block.getForeground() != "") {
                    foregroundText.loadFromFile(block.getForeground());
                    foreground.setTexture(foregroundText);
                    foreground.setPosition(posX * 32, posY * 32);
                    foreground.setScale(0.5, 0.5);
                    _window.draw(foreground);
                }
            }
        }
    }
    foreground.~Sprite();
    background.~Sprite();
    foregroundText.~Texture();
    backgroundText.~Texture();
    _window.display();
}

void acd::graphicSfml::getInputs()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            addInput(Input::KEY_ESCAPE);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            addInput(Input::KEY__LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            addInput(Input::KEY__RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            addInput(Input::KEY__UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            addInput(Input::KEY__DOWN);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            addInput(Input::KEY_SPACE);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            addInput(Input::KEY_A);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            addInput(Input::KEY_B);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            addInput(Input::KEY_C);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            addInput(Input::KEY_D);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            addInput(Input::KEY_E);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            addInput(Input::KEY_F);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            addInput(Input::KEY_G);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            addInput(Input::KEY_H);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            addInput(Input::KEY_I);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            addInput(Input::KEY_J);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            addInput(Input::KEY_K);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            addInput(Input::KEY_L);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            addInput(Input::KEY_M);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            addInput(Input::KEY_N);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            addInput(Input::KEY_O);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            addInput(Input::KEY_P);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            addInput(Input::KEY_Q);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            addInput(Input::KEY_R);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            addInput(Input::KEY_S);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            addInput(Input::KEY_T);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            addInput(Input::KEY_U);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            addInput(Input::KEY_V);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            addInput(Input::KEY_W);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            addInput(Input::KEY_X);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            addInput(Input::KEY_Y);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            addInput(Input::KEY_Z);
    }

}

void acd::graphicSfml::setRefBlocks(const std::map<std::string, std::reference_wrapper<acd::IBlock>> &refBlocks)
{
    _refBlocks = refBlocks;
}

const std::map<std::string, std::reference_wrapper<acd::IBlock>> &acd::graphicSfml::getRefBlocks() const
{
    return _refBlocks;
}

acd::IBlock &acd::graphicSfml::getRefBlock(const std::string &name) const
{
    return _refBlocks.at(name);
}

void acd::graphicSfml::_createRefBlocks()
{
    std::map<std::string, std::reference_wrapper<acd::IBlock>> blocks;
    blocks.emplace("wall", std::ref(acd::ABlocks("assets/wall.png", "")));
    blocks.emplace("snake_end_down", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-end-down.png")));
    blocks.emplace("snake_end_left", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-end-left.png")));
    blocks.emplace("snake_end_right", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-end-right.png")));
    blocks.emplace("snake_end_up", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-end-up.png")));
    blocks.emplace("snake_body_horizontal", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-body-horizontal.png")));
    blocks.emplace("snake_body_vertical", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-body-vertical.png")));
    blocks.emplace("snake_turn_left_down", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-turn-left-down.png")));
    blocks.emplace("snake_turn_left_up", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-turn-left-up.png")));
    blocks.emplace("snake_turn_right_down", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-turn-right-down.png")));
    blocks.emplace("snake_turn_right_up", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-turn-right-up.png")));
    blocks.emplace("snake_head_down", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-head-down.png")));
    blocks.emplace("snake_head_left", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-head-left.png")));
    blocks.emplace("snake_head_right", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-head-right.png")));
    blocks.emplace("snake_head_up", std::ref(acd::ABlocks("assets/grassdark.png", "assets/snake-head-up.png")));
    blocks.emplace("apple", std::ref(acd::ABlocks("assets/grassdark.png", "assets/apple.png")));
    blocks.emplace("grassdark", std::ref(acd::ABlocks("assets/grassdark.png", "")));
    setRefBlocks(blocks);
}
