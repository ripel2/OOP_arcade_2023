/*
** EPITECH PROJECT, 2023
** arcadedev
** File description:
** sfml
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "IDisplayModule.hpp"


namespace acd {
    class sfml : public IDisplayModule{
        public :
            /**
             * @brief Construct a new sfml object
             */
            sfml();
            /**
             * @brief Destroy the sfml object
             */
            ~sfml();
            /**
             * @brief Set the grid size of the display module
             * @param lines The number of lines
             * @param cols The number of columns
            */
            void setGridSize(std::size_t lines, std::size_t cols);
            /**
             * @brief Get the grid size of the display module
             * @return A pair containing the number of lines and the number of columns
            */
            std::pair<std::size_t, std::size_t> getGridSize() const;
            /**
             * @brief Set the list of blocks of the display module
             * @param blocks The list of blocks
            */
            std::vector<std::vector<std::reference_wrapper<Block>>> &getBlocks();
            /**
             * @brief Set all the blocks of the display module to black
            */
            void clearBlocks();
            /**
             * @brief Remove all the blocks of the display module
            */
            void removeBlocks();
            /**
             * @brief Set a block of the display module
             * @param line The line of the block
             * @param col The column of the block
             * @param block The block
            */
            void setBlock(std::size_t line, std::size_t col, Block &block);
            /**
             * @brief Get a block of the display module
             * @param line The line of the block
             * @param col The column of the block
             * @return The block
            */
            Block &getBlock(std::size_t line, std::size_t col);
            /**
             * @brief Clears a block of the display module
             * @param line The line of the block
             * @param col The column of the block
            */
            void clearBlock(std::size_t line, std::size_t col);
            /**
             * @brief Adds a text block to the display module
             * @param name The name of the text block
             * @param textBlock The text block to add
            */
            void addTextBlock(const std::string &name, TextBlock &textBlock);
            /**
             * @brief Gets a text block from the display module
             * @param name The name of the text block to get
            */
            TextBlock &getTextBlock(const std::string &name);
            /**
             * @brief Removes a text block from the display module
             * @param name The name of the text block to remove
            */
            void removeTextBlock(const std::string &name);
            /**
             * @brief Removes all the text blocks of the display module
            */
            void removeTextBlocks();
            /**
             * @brief Get the input of the display module
             * @return The input of the display module
            */
            Input getInput();
            /**
             * @brief Display the display module
            */
            void display();
            /**
             * @brief Get latest keyboard input
             * @return The latest keyboard input
             */
            Input getLatestKeyboardInput() const;


        protected :
        private :
            sf::RenderWindow _window;
            Input _input;
            std::pair<std::size_t, std::size_t> _gridSize;
            std::vector<std::vector<std::reference_wrapper<Block>>>  &_blocks;
    };
}
