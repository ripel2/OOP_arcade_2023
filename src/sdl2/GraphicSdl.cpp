/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu-20.04]
** File description:
** graphicSdl
*/

#include "GraphicSdl.hpp"

acd::graphicSdl::graphicSdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init failed load library "<< std::endl;
    }
    if (TTF_Init() == -1) {
        std::cerr << "Error initializing TTF: " << TTF_GetError() << std::endl;
    }
    if (SDL_RWFromFile("src/assets/arial.ttf", "rb") == nullptr) {
        std::cerr << "Error loading font file: " << SDL_GetError() << std::endl;
        exit(84);
    } else {
        _font = TTF_OpenFont("src/assets/arial.ttf", 32);
    }
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

acd::graphicSdl::~graphicSdl()
{
    SDL_RenderClear(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void acd::graphicSdl::display(GameMap const &map)
{
    std::pair<std::size_t, std::size_t> size = map.getSize();
    std::map<std::pair<std::size_t, std::size_t>, std::reference_wrapper<Block>> grid = map.getGrid();
    std::map<std::string, std::reference_wrapper<acd::TextBlock>> texts = map.getTexts();
    SDL_Rect backgroundRect;
    SDL_Surface* backgroundSurface;
    SDL_Texture* backgroundTexture;
    SDL_Surface* foregroundSurface;
    SDL_Texture* foregroundTexture;
    SDL_Rect foregroundRect;

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    for (std::size_t x = 0; x < size.first; x++) {
        for (std::size_t y = 0; y < size.second; y++) {
            if (grid.find({x, y}) != grid.end()) {
                acd::Block &block = grid.at({x, y}).get();
                std::size_t posX = x;
                std::size_t posY = y;
                if (block.getBackgroundPath() == "") {
                    setColorToSdlColor(block.getBackgroundColorNcurses());
                    backgroundRect.x = posX * 32;
                    backgroundRect.y = posY * 32;
                    backgroundRect.w = 32;
                    backgroundRect.h = 32;
                    SDL_RenderFillRect(_renderer, &backgroundRect);
                } else {
                    backgroundSurface = SDL_LoadBMP(block.getBackgroundPath().c_str());
                    backgroundTexture = SDL_CreateTextureFromSurface(_renderer, backgroundSurface);
                    SDL_FreeSurface(backgroundSurface);
                    backgroundRect.x = posX * 32;
                    backgroundRect.y = posY * 32;
                    backgroundRect.w *= 0.5;
                    backgroundRect.h *= 0.5;
                    SDL_RenderCopy(_renderer, backgroundTexture, NULL, &backgroundRect);
                    if (block.getForegroundPath() != "") {
                        foregroundSurface = SDL_LoadBMP(block.getForegroundPath().c_str());
                        foregroundTexture = SDL_CreateTextureFromSurface(_renderer, foregroundSurface);
                        SDL_FreeSurface(foregroundSurface);
                        foregroundRect.x = posX * 32;
                        foregroundRect.y = posY * 32;
                        foregroundRect.w *= 0.5;
                        foregroundRect.h *= 0.5;
                        SDL_RenderCopy(_renderer, foregroundTexture, NULL, &foregroundRect);
                    }
                }
            }
        }
    }
    for (auto &textBlock : texts) {
        std::pair<std::size_t, std::size_t> pos = textBlock.second.get().getTextPosition();
        SDL_Color color = getColorToSdlColor(textBlock.second.get().getColor());
        if (color.r == 0 && color.g == 0 && color.b == 0) {
            color.r = 0;
            color.g = 255;
            color.b = 255;
        }
        SDL_Surface *surface = TTF_RenderText_Solid(_font, textBlock.second.get().getText().c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_FreeSurface(surface);
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        SDL_Rect dstrect = { (int) pos.second * 64, (int) pos.first * 32, width, height };
        SDL_RenderCopy(_renderer, texture, NULL, &dstrect);
    }
    SDL_RenderPresent(_renderer);
}

SDL_Color acd::graphicSdl::getColorToSdlColor(acd::Color color)
{
    if (color == acd::Color::BLACK || color == acd::Color::LIGHT_BLACK) {
        return SDL_Color{0, 0, 0, 255};
    } else if (color == acd::Color::RED || color == acd::Color::LIGHT_RED) {
        return SDL_Color{255, 0, 0, 255};
    } else if (color == acd::Color::GREEN || color == acd::Color::LIGHT_GREEN) {
        return SDL_Color{0, 255, 0, 255};
    } else if (color == acd::Color::YELLOW || color == acd::Color::LIGHT_YELLOW) {
        return SDL_Color{255, 255, 0, 255};
    } else if (color == acd::Color::BLUE || color == acd::Color::LIGHT_BLUE) {
        return SDL_Color{0, 0, 255, 255};
    } else if (color == acd::Color::MAGENTA || color == acd::Color::LIGHT_MAGENTA) {
        return SDL_Color{255, 0, 255, 255};
    } else if (color == acd::Color::CYAN || color == acd::Color::LIGHT_CYAN) {
        return SDL_Color{0, 255, 255, 255};
    } else if (color == acd::Color::WHITE || color == acd::Color::LIGHT_WHITE) {
        return SDL_Color{255, 255, 255, 255};
    } else {
        return SDL_Color{0, 0, 0, 255};
    }
}

void  acd::graphicSdl::setColorToSdlColor(acd::Color color)
{
    if (color == acd::Color::BLACK || color == acd::Color::LIGHT_BLACK) {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    } else if (color == acd::Color::RED || color == acd::Color::LIGHT_RED) {
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    } else if (color == acd::Color::GREEN || color == acd::Color::LIGHT_GREEN) {
        SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
    } else if (color == acd::Color::YELLOW || color == acd::Color::LIGHT_YELLOW) {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
    } else if (color == acd::Color::BLUE || color == acd::Color::LIGHT_BLUE) {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    } else if (color == acd::Color::MAGENTA || color == acd::Color::LIGHT_MAGENTA) {
        SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
    } else if (color == acd::Color::CYAN || color == acd::Color::LIGHT_CYAN) {
        SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
    } else if (color == acd::Color::WHITE || color == acd::Color::LIGHT_WHITE) {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    } else {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }
}

void acd::graphicSdl::getInputs()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            addInput(Input::KEY__ESCAPE);
            SDL_DestroyWindow(_window);
            SDL_Quit();
            exit(0);
        }
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            addInput(Input::KEY__ESCAPE);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT)
            addInput(Input::KEY__LEFT);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT)
            addInput(Input::KEY__RIGHT);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
            addInput(Input::KEY__UP);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN)
            addInput(Input::KEY__DOWN);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
            addInput(Input::KEY__SPACE);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN)
            addInput(Input::KEY__ENTER);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_a)
            addInput(Input::KEY__A);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_b)
            addInput(Input::KEY__B);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_c)
            addInput(Input::KEY__C);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_d)
            addInput(Input::KEY__D);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_e)
            addInput(Input::KEY__E);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_f)
            addInput(Input::KEY__F);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_g)
            addInput(Input::KEY__G);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_h)
            addInput(Input::KEY__H);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_i)
            addInput(Input::KEY__I);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_j)
            addInput(Input::KEY__J);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_k)
            addInput(Input::KEY__K);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_l)
            addInput(Input::KEY__L);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m)
            addInput(Input::KEY__M);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_n)
            addInput(Input::KEY__N);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_o)
            addInput(Input::KEY__O);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_p)
            addInput(Input::KEY__P);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)
            addInput(Input::KEY__Q);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r)
            addInput(Input::KEY__R);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_s)
            addInput(Input::KEY__S);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_t)
            addInput(Input::KEY__T);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_u)
            addInput(Input::KEY__U);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_v)
            addInput(Input::KEY__V);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_w)
            addInput(Input::KEY__W);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_x)
            addInput(Input::KEY__X);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_y)
            addInput(Input::KEY__Y);
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_z)
            addInput(Input::KEY__Z);
    }
}
