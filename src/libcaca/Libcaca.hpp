/*
** EPITECH PROJECT, 2023
** ArcadeShared [WSL: Ubuntu]
** File description:
** Libcaca
*/

#pragma once

#include "AGraphicModule.hpp"
#include "Inputs.hpp"
#include "GameMap.hpp"

#include <memory>

#include <caca.h>

namespace acd {
    class Libcaca : public AGraphicModule {
        public:
            /**
             * @brief Construct a new Libcaca object
             */
            Libcaca();
            /**
             * @brief Destroy the Libcaca object
             */
            ~Libcaca() override;

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
            caca_canvas_t *_canvas;
            caca_display_t *_display;

            enum caca_color _convertColor(acd::Color color);
    };
}
