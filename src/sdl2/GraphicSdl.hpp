/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu-20.04]
** File description:
** GraphicSdl
*/

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

#include "AGraphicModule.hpp"
#include "Inputs.hpp"
#include "GameMap.hpp"

namespace acd {
    class GraphicSdl : public AGraphicModule {
        public:
            /**
             * @brief Construct a new GraphicSdl object
             */
            GraphicSdl();

            /**
             * @brief Destroy the GraphicSdl object
             */
            ~GraphicSdl();

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
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            SDL_Texture *_texture;
            SDL_Event _event;

    };
}
