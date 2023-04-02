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
            void setRefBlocks(const std::map<std::string, std::reference_wrapper<acd::IBlock>> &refBlocks) override;
            const std::map<std::string, std::reference_wrapper<IBlock>> &getRefBlocks() const override;
            IBlock &getRefBlock(const std::string &name) const override;
        private:
            std::map<std::string, std::reference_wrapper<IBlock>> _refBlocks;
    };
}
