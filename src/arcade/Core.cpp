/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"

acd::Core::Core(const char *lib)
{
    _startLibPath = "";
    _isReady = false;
    if (!std::filesystem::exists(lib))
        throw CoreException("library " + std::string(lib) + " does not exist");
    _startLibPath = lib;
    _graphicLibs = std::vector<std::pair<std::string, std::unique_ptr<DLLoader<IGraphicModule>>>>();
    _gameLibs = std::vector<std::pair<std::string, std::unique_ptr<DLLoader<IGameModule>>>>();
    _gameLibIndex = 0;
    _graphicLibIndex = 0;
    _graphicLib = nullptr;
    _gameLib = nullptr;
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
                _graphicLibs.push_back(std::make_pair(entry.path(), std::move(lib)));
                if (entry.path() == _startLibPath)
                    _graphicLibIndex = _graphicLibs.size() - 1;
            } catch (const std::exception &e) {
                try {
                    std::unique_ptr<DLLoader<IGameModule>> lib = getGameLib(entry.path());
                    _gameLibs.push_back(std::make_pair(entry.path(), std::move(lib)));
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

void acd::Core::setupMenu(acd::Menu &menu)
{
    std::vector<std::string> graphicLibsPaths;
    for (const auto &lib : _graphicLibs)
        graphicLibsPaths.push_back(lib.first);
    menu.setAvailableGraphicLibs(graphicLibsPaths);
    std::vector<std::string> gameLibsPaths;
    for (const auto &lib : _gameLibs)
        gameLibsPaths.push_back(lib.first);
    menu.setAvailableGameLibs(gameLibsPaths);
}

void acd::Core::_updateLibs(acd::updateType_t update)
{
    if (update == acd::updateType_t::NEXTGRAPHIC) {
        _graphicLibIndex++;
        if (_graphicLibIndex >= _graphicLibs.size())
            _graphicLibIndex = 0;
        _graphicLib = std::move(_graphicLibs[_graphicLibIndex].second->getInstance());
    } else if (update == acd::updateType_t::PREVGRAPHIC) {
        _graphicLibIndex--;
        if (_graphicLibIndex < 0)
            _graphicLibIndex = _graphicLibs.size() - 1;
        _graphicLib = std::move(_graphicLibs[_graphicLibIndex].second->getInstance());
    } else if (update == acd::updateType_t::NEXTGAME) {
        _gameLibIndex++;
        if (_gameLibIndex >= _gameLibs.size())
            _gameLibIndex = 0;
        _gameLib = std::move(_gameLibs[_gameLibIndex].second->getInstance());
    } else if (update == acd::updateType_t::PREVGAME) {
        _gameLibIndex--;
        if (_gameLibIndex < 0)
            _gameLibIndex = _gameLibs.size() - 1;
        _gameLib = std::move(_gameLibs[_gameLibIndex].second->getInstance());
    }
}

void acd::Core::startMenu()
{
    acd::Menu menu;

    _graphicLib = std::move(_graphicLibs[_graphicLibIndex].second->getInstance());
    setupMenu(menu);
    while (!menu.isReady()) {
        _graphicLib->getInputs();
        acd::Input input = _graphicLib->getLatestInput();
        if (input == acd::Input::KEY__ESCAPE) {
            break;
        }
        acd::updateType_t update = menu.update(input);
        _updateLibs(update);
        _graphicLib->display(menu.getMap());
    }
    if (menu.isReady()) {
        _isReady = true;
        _username = menu.getUsername();
        for (const auto &lib : _gameLibs) {
            if (lib.first == menu.getSelectedGameLib())
                break;
            _gameLibIndex++;
        }
        for (const auto &lib : _graphicLibs) {
            if (lib.first == menu.getSelectedGraphicLib())
                break;
            _graphicLibIndex++;
        }
    }
}

bool acd::Core::isReady() const
{
    return _isReady;
}

void acd::Core::startGame()
{
    _graphicLib = std::move(_graphicLibs[_graphicLibIndex].second->getInstance());
    _gameLib  = std::move(_gameLibs[_gameLibIndex].second->getInstance());
    while (1) {
        _graphicLib->getInputs();
        acd::Input input = _graphicLib->getLatestInput();
        if (input == acd::Input::KEY__ESCAPE) {
            break;
        }
        acd::updateType_t update = _gameLib->update(input);
        _updateLibs(update);
        _graphicLib->display(_gameLib->getMap());
    }
}
