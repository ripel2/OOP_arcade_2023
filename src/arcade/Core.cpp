/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"

acd::Core::Core(const char *lib)
{
    if (!std::filesystem::exists(lib))
        throw CoreException("library " + std::string(lib) + " does not exist");
    _startLib = getGraphicLib(lib);
    _graphicLibs = std::map<std::string, std::unique_ptr<DLLoader<IGraphicModule>>>();
    _gameLibs = std::map<std::string, std::unique_ptr<DLLoader<IGameModule>>>();
}

acd::Core::~Core()
{
}

void acd::Core::loadLibsFromFolder(const std::string &folder)
{
    std::filesystem::path path(folder);
    if (!std::filesystem::exists(path))
        throw CoreException("folder " + folder + " does not exist");
    if (!std::filesystem::is_directory(path))
        throw CoreException(folder + " is not a folder");
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".so") {
            try {
                std::unique_ptr<DLLoader<IGraphicModule>> lib = getGraphicLib(entry.path());
                _graphicLibs[entry.path().generic_string()] = std::move(lib);
            } catch (const std::exception &e) {
                try {
                    std::unique_ptr<DLLoader<IGameModule>> lib = getGameLib(entry.path());
                    _gameLibs[entry.path().generic_string()] = std::move(lib);
                } catch (const std::exception &e) {
                    throw CoreException("library " + entry.path().generic_string() + " is not a graphic or a game library");
                }
            }
        }
    }
    if (_graphicLibs.empty())
        throw CoreException("no graphic library found in folder " + folder);
    if (_gameLibs.empty())
        throw CoreException("no game library found in folder " + folder);
}

std::unique_ptr<acd::DLLoader<acd::IGraphicModule>> acd::Core::getGraphicLib(const std::string &lib)
{
    try {
        return std::make_unique<DLLoader<IGraphicModule>>(lib, "graphicEntryPoint");
    } catch (const std::exception &e) {
        throw CoreException("library " + lib + " is not a graphic library");
    }
}

std::unique_ptr<acd::DLLoader<acd::IGameModule>> acd::Core::getGameLib(const std::string &lib)
{
    try {
        return std::make_unique<DLLoader<IGameModule>>(lib, "gameEntryPoint");
    } catch (const std::exception &e) {
        throw CoreException("library " + lib + " is not a game library");
    }
}

void acd::Core::startMenu()
{
    acd::GameMap map(24, 80);
    size_t line = 0;

    std::unique_ptr<IGraphicModule> lib = std::move(_startLib->getInstance());
    while (1) {
        lib.get()->getInputs();
        acd::Input input = lib.get()->getLatestInput();
        if (input == acd::Input::KEY_ESCAPE)
            break;
        lib.get()->display(map);
    }
}

void acd::Core::startGame()
{

}