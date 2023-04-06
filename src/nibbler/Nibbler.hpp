/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Snake
*/

#pragma once

#include "IGameModule.hpp"
#include "AGameModule.hpp"
#include "Block.hpp"
#include "TextBlock.hpp"

#include <chrono>
#include <memory>

namespace acd {
    class Nibbler : public AGameModule {
        public:
            Nibbler();
            ~Nibbler() = default;
            updateType_t update(Input latestInput);
            void pause();
            void play();
            void restart();
        private:
            GameMap _map;
            std::vector<std::unique_ptr<Block>> _blocks;
            std::vector<std::unique_ptr<TextBlock>> _textBlocks;
            std::vector<std::pair<int, int>> _nibbler;
            bool _isPaused;
            int _direction;
            bool _isGameOver;
            bool _movedOnce;
            std::pair<int, int> _food;
            std::chrono::time_point<std::chrono::system_clock> _lastUpdate;
            void _setMap();
            void _initNibbler();
            void _setGameOver();
    };
}