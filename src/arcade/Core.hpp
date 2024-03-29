/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Core
*/

#pragma once

#include <exception>
#include <string>
#include <filesystem>
#include <memory>

#include "IGraphicModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"
#include "Menu.hpp"
#include "Error.hpp"

namespace acd {
    class Core {
        public:
            Core(const char *lib);
            ~Core();
            class CoreException : public std::exception {
                public:
                    CoreException(const std::string &message)
                    {
                        _message = "core exception: " + message;
                    }
                    ~CoreException() = default;
                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }
                private:
                    std::string _message;
            };
            /**
             * @brief Load all the libraries from a folder
             * @param folder
            */
            void loadLibsFromFolder(const std::string &folder);
            /**
             * @brief Starts the start menu
            */
            void startMenu();
            /**
             * @brief Starts the main loop
            */
            void startGame();
            /**
             * @brief Checks if the core is ready to start the game
             * @return true if the core is ready, false otherwise
            */
            bool isReady() const;
        protected:
        private:
            std::string _startLibPath;
            std::vector<std::pair<std::string, std::unique_ptr<DLLoader<IGraphicModule>>>> _graphicLibs;
            std::vector<std::pair<std::string, std::unique_ptr<DLLoader<IGameModule>>>> _gameLibs;
            bool _isReady;
            std::size_t _graphicLibIndex;
            std::unique_ptr<acd::IGraphicModule> _graphicLib;
            std::size_t _gameLibIndex;
            std::unique_ptr<acd::IGameModule> _gameLib;
            std::string _username;
            /**
             * @brief Checks if the library is a graphic library and returns its
             * DLLoader if it is, else it throws an exception
            */
            std::unique_ptr<DLLoader<IGraphicModule>> getGraphicLib(const std::string &lib);
            /**
             * @brief Checks if the library is a game library and returns its
             * DLLoader if it is, else it throws an exception
            */
            std::unique_ptr<DLLoader<IGameModule>> getGameLib(const std::string &lib);
            /**
             * @brief Set the menu up
            */
            void setupMenu(acd::Menu &menu);
            void _updateLibs(acd::updateType_t update);
    };
}
