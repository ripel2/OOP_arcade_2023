/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu-20.04]
** File description:
** GraphicSdl
*/

#include "GraphicSdl.hpp"

acd::GraphicSdl::GraphicSdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init failed load library "<< std::endl;
        exit(1);
    }
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
}

acd::GraphicSdl::~GraphicSdl()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void acd::GraphicSdl::display(GameMap const &map)
{
    std::pair<std::size_t, std::size_t> size = map.getSize();
    //std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<Block>> grid = map.getBlock();
    std::map<std::string, std::reference_wrapper<acd::TextBlock>> texts = map.getTexts();
}

void acd::GraphicSdl::getInputs()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            exit(0);
    }
}
