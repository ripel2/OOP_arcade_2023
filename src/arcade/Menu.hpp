/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Menu
*/

#pragma once

#include <iostream>
#include <memory>

#include "IGameModule.hpp"
#include "AGameModule.hpp"
#include "Block.hpp"
#include "TextBlock.hpp"

namespace acd {
    // Menu is a special module so we allow it to have some different functions
    class Menu : public AGameModule {
        public:
            Menu();
            ~Menu() = default;

            void setAvailableGraphicLibs(const std::vector<std::string> &libs);
            void setAvailableGameLibs(const std::vector<std::string> &libs);
            updateType_t update(Input latestInput) override;
            void pause() override { };
            void play() override { };
            void restart() override { };
            std::string getSelectedGraphicLib() const { return _selectedGraphicLibPath; };
            std::string getSelectedGameLib() const { return _selectedGameLibPath; }
            std::string getUsername() const { return std::string(_username); }
            bool isReady() const { return _selectedGraphicLib && _selectedGameLib && _typedUsername; }
        private:
            std::vector<std::string> _availableGraphicLibs;
            std::vector<std::string> _availableGameLibs;
            std::string _selectedGraphicLibPath;
            std::string _selectedGameLibPath;
            std::size_t _selectedGraphicLibIndex;
            std::size_t _selectedGameLibIndex;
            std::size_t _usernameCursorIndex;
            bool _selectedGraphicLib;
            bool _selectedGameLib;
            bool _typedUsername;
            GameMap _map;
            // There is a maximum of 10 characters for the username so we alloc 11 chars
            char _username[10 + 1];
            std::vector<std::unique_ptr<Block>> _blocks;
            std::vector<std::unique_ptr<TextBlock>> _textBlocks;
            void arrowUp();
            void arrowDown();
            void arrowLeft();
            void arrowRight();
            void pressEnter();
            void updateMap();
            void addCharToUsername(Input latestInput);
            void _initTitleBlocks();
            void _initOptionBlocks();
            void _initUsernameChars();
    };
}
