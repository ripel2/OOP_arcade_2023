/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu]
** File description:
** ATextBlock
*/

#pragma once

#include "ITextBlock.hpp"

namespace acd {
    class ATextBlock : public ITextBlock {
        public:
            /**
             * @brief Constructor of the text block
            */
            ATextBlock() = default;
            /**
             * @brief Destructor of the text block
            */
            ~ATextBlock() = default;

            /**
             * @brief Set the position of the text block
            */
            void setPosition(std::size_t line, std::size_t col) override;
            /**
             * @brief Get the position of the text block
             * @return A pair containing the line and the column
            */
            std::pair<std::size_t, std::size_t> getPosition() const override;
            /**
             * @brief Set the text of the text block
             * @param text The text of the text block
            */
            void setText(const std::string &text) override;
            /**
             * @brief Get the text of the text block
             * @return The text of the text block
            */
            std::string getText() const override;
            /**
             * @brief Set the color of the text block foreground
             * @param color The color of the text block foreground
            */
            void setForeColor(Color color) override;
            /**
             * @brief Get the color of the text block foreground
             * @return The color of the text block foreground
            */
            Color getForeColor() const override;
            /**
             * @brief Set the color of the text block background
             * @param color The color of the text block background
            */
            void setBackColor(Color color) override;
            /**
             * @brief Get the color of the text block background
             * @return The color of the text block background
            */
            Color getBackColor() const override;
        private:
            std::size_t _line;
            std::size_t _col;
            std::string _text;
            Color _foreColor;
            Color _backColor;
    };
}
