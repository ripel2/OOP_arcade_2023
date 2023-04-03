/*
** EPITECH PROJECT, 2023
** ArcadeShared [WSL: Ubuntu]
** File description:
** Ncurses
*/

#pragma once

#include "AGraphicModule.hpp"
#include "Inputs.hpp"
#include "GameMap.hpp"

#include <memory>

namespace acd {
    class Ncurses : public AGraphicModule {
        public:
            /**
             * @brief Construct a new Ncurses object
             */
            Ncurses();
            /**
             * @brief Destroy the Ncurses object
             */
            ~Ncurses() override;

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
            std::map<std::string, std::reference_wrapper<Block>> _refBlocks;
            // foreground color, background color, pair number, is bright
            std::map<std::pair<acd::Color, acd::Color>, std::pair<int, bool>> _colorPairs;
            void _initColors();
            void _attrOnColors(acd::Color foreColor, acd::Color backColor);
            void _attrOffColors(acd::Color foreColor, acd::Color backColor);
    };
}
