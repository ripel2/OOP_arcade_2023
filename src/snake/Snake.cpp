/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Snake
*/

#include "Snake.hpp"

acd::Snake::Snake()
    : AGameModule(), _map(31, 31), _isPaused(false), _direction(0), _isGameOver(false), _lastUpdate(std::chrono::system_clock::now())
{
    _isPaused = false;
    _blocks = std::vector<std::unique_ptr<ABlock>>();
    _textBlocks = std::vector<std::unique_ptr<ATextBlock>>();
    std::unique_ptr<ABlock> snakeBlock = std::make_unique<ABlock>();
    char blockchars[2] = {' ', ' '};
    snakeBlock.get()->loadTexturesNcurses(Color::WHITE, Color::BLUE, blockchars);
    _blocks.push_back(std::move(snakeBlock));
    std::unique_ptr<ABlock> wallBlock = std::make_unique<ABlock>();
    char wallchars[2] = {' ', ' '};
    wallBlock.get()->loadTexturesNcurses(Color::WHITE, Color::RED, wallchars);
    _blocks.push_back(std::move(wallBlock));
    for (std::size_t y = 0; y < 31; y++) {
        _map.setBlock(0, y, *_blocks[1].get());
        _map.setBlock(30, y, *_blocks[1].get());
    }
    for (std::size_t x = 0; x < 31; x++) {
        _map.setBlock(x, 0, *_blocks[1].get());
        _map.setBlock(x, 30, *_blocks[1].get());
    }
    _initSnake();
    setMap(_map);
}

void acd::Snake::_initSnake()
{
    for (std::size_t x = 1; x < 30; x++)
        for (std::size_t y = 1; y < 30; y++)
            _map.removeBlock(x, y);
    _snake = std::vector<std::pair<int, int>>();
    _direction = 0;
    _snake.push_back(std::pair<int, int>(15, 15));
    _snake.push_back(std::pair<int, int>(15, 14));
    _snake.push_back(std::pair<int, int>(15, 13));
    _snake.push_back(std::pair<int, int>(15, 12));
    _snake.push_back(std::pair<int, int>(15, 11));
    _snake.push_back(std::pair<int, int>(15, 10));
    _snake.push_back(std::pair<int, int>(15, 9));
    _snake.push_back(std::pair<int, int>(15, 8));
    _snake.push_back(std::pair<int, int>(15, 7));
    _snake.push_back(std::pair<int, int>(15, 6));
    for (std::size_t c = 0; c < _snake.size(); c++)
        _map.setBlock(_snake[c].first, _snake[c].second, *_blocks[0].get());
    setScore(0);
    setMap(_map);
}

acd::updateType_t acd::Snake::update(Input latestInput)
{
    if (latestInput == Input::KEY_P) {
        _isPaused = !_isPaused;
    }
    if (latestInput == Input::KEY_R) {
        _initSnake();
        _isGameOver = false;
        _isPaused = false;
    }
    if (_isPaused || _isGameOver)
        return acd::updateType_t::UPDATE_NONE;
    switch (latestInput) {
        case Input::KEY_S:
            _direction = _direction == 2 ? 2 : 0;
            break;
        case Input::KEY_D:
            _direction = _direction == 3 ? 3 : 1;
            break;
        case Input::KEY_Z:
            _direction = _direction == 0 ? 0 : 2;
            break;
        case Input::KEY_Q:
            _direction = _direction == 1 ? 1 : 3;
            break;
        default:
            break;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _lastUpdate).count() < 100)
        return acd::updateType_t::UPDATE_NONE;
    for (std::size_t c = 0; c < _snake.size(); c++)
        _map.removeBlock(_snake[c].first, _snake[c].second);
    switch (_direction) {
        case 0:
            _snake.insert(_snake.begin(), std::pair<int, int>(_snake[0].first, _snake[0].second + 1));
            break;
        case 1:
            _snake.insert(_snake.begin(), std::pair<int, int>(_snake[0].first + 1, _snake[0].second));
            break;
        case 2:
            _snake.insert(_snake.begin(), std::pair<int, int>(_snake[0].first, _snake[0].second - 1));
            break;
        case 3:
            _snake.insert(_snake.begin(), std::pair<int, int>(_snake[0].first - 1, _snake[0].second));
            break;
        default:
            break;
    }
    _snake.pop_back();
    for (std::size_t c = 0; c < _snake.size(); c++) {
        if (_snake[c].first == 0 || _snake[c].first == 30 || _snake[c].second == 0 || _snake[c].second == 30) {
            _isGameOver = true;
        } else {
            _map.setBlock(_snake[c].first, _snake[c].second, *_blocks[0].get());
        }
    }
    setMap(_map);
    _lastUpdate = std::chrono::system_clock::now();
    return acd::updateType_t::UPDATE_NONE;
}

void acd::Snake::pause()
{
    _isPaused = true;
}

void acd::Snake::play()
{
    _isPaused = false;
}

void acd::Snake::restart()
{

}

