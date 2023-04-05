/*
** EPITECH PROJECT, 2023
** arcadedev
** File description:
** graphicsfml
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "AGraphicModule.hpp"
#include "GameMap.hpp"


namespace acd {
    class graphicSfml : public AGraphicModule{
        public :
            /**
             * @brief Construct a new sfml object
             */
            graphicSfml();
            /**
             * @brief Destroy the sfml object
             */
            ~graphicSfml();
            /**
             * @brief Display the game
             * @param map the map
             */
            void display(GameMap const &map);
            /**
             * @brief Get the Inputs object
             */
            void getInputs();
            void setRefBlocks(const std::map<std::string, std::reference_wrapper<Block>> &refBlocks);
            const std::map<std::string, std::reference_wrapper<Block>> &getRefBlocks() const;
            Block &getRefBlock(const std::string &name) const;

        protected :
        private :
            sf::RenderWindow _window;
            std::map<std::string, std::reference_wrapper<Block>>  _refBlocks;
            sf::Color getColorToSfmlColor(Color color);
    };
}
