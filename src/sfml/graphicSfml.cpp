/*
** EPITECH PROJECT, 2023
** arcadedevparty
** File description:
** graphicSfml
*/

#include "graphicSfml.hpp"

acd::graphicSfml::graphicSfml()
{
    if (!_font.loadFromFile("src/assets/arial.ttf"))
        throw std::runtime_error("Error: Font not found");

    if (!_window.isOpen())
        _window.create(sf::VideoMode(1920, 1080), "Arcade");
    _window.setFramerateLimit(60);
}

acd::graphicSfml::~graphicSfml()
{
    _font.~Font();
    _window.close();
    _window.~RenderWindow();
}

void acd::graphicSfml::display(GameMap const &map)
{
    std::pair<std::size_t, std::size_t> size = map.getSize();
    std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<acd::Block>> grid = map.getGrid();
    std::map<std::string, std::reference_wrapper<acd::TextBlock>> texts = map.getTexts();
    sf::Text text = sf::Text();
    sf::Sprite foreground = sf::Sprite();
    sf::Texture foregroundText = sf::Texture();
    sf::Sprite background = sf::Sprite();
    sf::Texture backgroundText = sf::Texture();
    sf::RectangleShape backgroundRec = sf::RectangleShape();

    _window.clear();
    for (std::size_t x = 0; x < size.first; x++) {
        for (std::size_t y = 0; y < size.second; y++) {
            if (grid.find({x, y}) != grid.end()) {
                acd::Block &block = grid.at({x, y}).get();
                std::size_t posX = x;
                std::size_t posY = y;
                if (block.getBackgroundPath() == "") {
                    backgroundRec.setPosition(posX * 32, posY * 32);
                    backgroundRec.setSize(sf::Vector2f(32, 32));
                    backgroundRec.setFillColor(getColorToSfmlColor(block.getBackgroundColorNcurses()));
                    _window.draw(backgroundRec);
                } else {
                    backgroundText.loadFromFile(block.getBackgroundPath());
                    background.setTexture(backgroundText);
                    background.setPosition(posX * 32, posY * 32);
                    background.setScale(0.5, 0.5);
                    _window.draw(background);
                }
                if (block.getForegroundPath() != "") {
                    foregroundText.loadFromFile(block.getForegroundPath());
                    foreground.setTexture(foregroundText);
                    foreground.setPosition(posX * 32, posY * 32);
                    foreground.setScale(0.5, 0.5);
                    _window.draw(foreground);
                }
            }
        }
    }
    for (auto &textBlock : texts) {
        std::pair<std::size_t, std::size_t> pos = textBlock.second.get().getTextPosition();
        text.setFont(_font);
        text.setString(textBlock.second.get().getText());
        text.setPosition(pos.second * 64, pos.first * 32);
        if (getColorToSfmlColor(textBlock.second.get().getColor()) == sf::Color::Black) {
            text.setFillColor(sf::Color::Cyan);
        } else {
            text.setFillColor(getColorToSfmlColor(textBlock.second.get().getColor()));
        }
        _window.draw(text);
    }
    foreground.~Sprite();
    background.~Sprite();
    foregroundText.~Texture();
    backgroundText.~Texture();
    _window.display();
}

sf::Color acd::graphicSfml::getColorToSfmlColor(acd::Color color)
{
    if (color == acd::Color::BLACK || color == acd::Color::LIGHT_BLACK)
        return sf::Color::Black;
    if (color == acd::Color::RED || color == acd::Color::LIGHT_RED)
        return sf::Color::Red;
    if (color == acd::Color::GREEN || color == acd::Color::LIGHT_GREEN)
        return sf::Color::Green;
    if (color == acd::Color::YELLOW || color == acd::Color::LIGHT_YELLOW)
        return sf::Color::Yellow;
    if (color == acd::Color::BLUE || color == acd::Color::LIGHT_BLUE)
        return sf::Color::Blue;
    if (color == acd::Color::MAGENTA || color == acd::Color::LIGHT_MAGENTA)
        return sf::Color::Magenta;
    if (color == acd::Color::CYAN || color == acd::Color::LIGHT_CYAN)
        return sf::Color::Cyan;
    if (color == acd::Color::WHITE || color == acd::Color::LIGHT_WHITE)
        return sf::Color::White;
    return sf::Color::Black;
}

void acd::graphicSfml::getInputs()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            addInput(Input::KEY__ESCAPE);
            _window.close();
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            addInput(Input::KEY__ESCAPE);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            addInput(Input::KEY__ESCAPE);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
            addInput(Input::KEY__LEFT);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
            addInput(Input::KEY__RIGHT);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
            addInput(Input::KEY__UP);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
            addInput(Input::KEY__DOWN);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            addInput(Input::KEY__SPACE);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            addInput(Input::KEY__ENTER);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
            addInput(Input::KEY__A);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
            addInput(Input::KEY__B);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C)
            addInput(Input::KEY__C);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
            addInput(Input::KEY__D);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E)
            addInput(Input::KEY__E);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F)
            addInput(Input::KEY__F);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::G)
            addInput(Input::KEY__G);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::H)
            addInput(Input::KEY__H);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::I)
            addInput(Input::KEY__I);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::J)
            addInput(Input::KEY__J);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::K)
            addInput(Input::KEY__K);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::L)
            addInput(Input::KEY__L);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::M)
            addInput(Input::KEY__M);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::N)
            addInput(Input::KEY__N);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::O)
            addInput(Input::KEY__O);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P)
            addInput(Input::KEY__P);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q)
            addInput(Input::KEY__Q);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
            addInput(Input::KEY__R);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
            addInput(Input::KEY__S);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::T)
            addInput(Input::KEY__T);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::U)
            addInput(Input::KEY__U);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::V)
            addInput(Input::KEY__V);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W)
            addInput(Input::KEY__W);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
            addInput(Input::KEY__X);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Y)
            addInput(Input::KEY__Y);
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z)
            addInput(Input::KEY__Z);
    }

}
