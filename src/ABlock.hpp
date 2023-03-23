/*
** EPITECH PROJECT, 2023
** ArcadeShared [WSL : Ubuntu-20.04]
** File description:
** ABlock
*/

#pragma once

#include "IBlock.hpp"

namespace acd {
    class ABlock : public IBlock {
        public:
            /**
             * @brief Constructor of the block
            */
            ABlock() = default;
            /**
             * @brief Destructor of the block
            */
            ~ABlock() = default;

            /**
             * @brief Set the color of the block foreground
            */
            void setForeColor(Color color) override;
            /**
             * @brief Get the color of the block foreground
             * @return The color of the block
            */
            Color getForeColor() const override;
            /**
             * @brief Set the color of the block background
            */
            void setBackColor(Color color) override;
            /**
             * @brief Get the color of the block background
             * @return The color of the block
            */
            Color getBackColor() const override;
            /**
             * @brief Set the text of the block (for terminal display)
            */
            void setText(const char *text) override;
            /**
             * @brief Get the text of the block (for terminal display)
             * @return The text of the block
            */
            const char *getText() const override;
            /**
             * @brief Set the path of the texture to display (for graphical display)
             * @param path The path of the texture
            */
            void setTexturePath(const char *path) override;
            /**
             * @brief Get the path of the texture to display (for graphical display)
             * @return The path of the texture
            */
            const char *getTexturePath() const override;
        private:
            Color _foreColor;
            Color _backColor;
            const char *_text;
            const char *_texturePath;
    };
}
