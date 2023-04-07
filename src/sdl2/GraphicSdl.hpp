/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu-20.04]
** File description:
** graphicSdl
*/

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <SDL2/SDL_ttf.h>

#include "AGraphicModule.hpp"
#include "Inputs.hpp"
#include "GameMap.hpp"

namespace acd {
    class graphicSdl : public AGraphicModule {
        public:
            /**
             * @brief Construct a new graphicSdl object
             */
            graphicSdl();

            /**
             * @brief Destroy the graphicSdl object
             */
            ~graphicSdl();

            /**
             * @brief Display the game
             * @param map the map
             */
            void display(GameMap const &map) override;

            /**
             * @brief Get the Users Inputs
             */
            void getInputs() override;

        private:
            void setColorToSdlColor(acd::Color color);
            SDL_Color getColorToSdlColor(acd::Color color);
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            SDL_Texture *_texture;
            SDL_Event _event;
            TTF_Font *_font;
    };
}
