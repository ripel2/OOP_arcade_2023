/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Snake
*/

#include "Snake.hpp"

acd::Snake::Snake()
    : AGameModule(), _map(31, 31), _isPaused(false), _direction(0), _isGameOver(false), _movedOnce(false), _lastUpdate(std::chrono::system_clock::now())
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
    _map.removeText("gameOver");
    for (std::size_t x = 1; x < 30; x++)
        for (std::size_t y = 1; y < 30; y++)
            _map.removeBlock(x, y);
    _snake = std::vector<std::pair<int, int>>();
    _direction = 0;
    _snake.push_back(std::pair<int, int>(15, 15));
    _snake.push_back(std::pair<int, int>(15, 14));
    _snake.push_back(std::pair<int, int>(15, 13));
    _snake.push_back(std::pair<int, int>(15, 12));
    for (std::size_t c = 0; c < _snake.size(); c++)
        _map.setBlock(_snake[c].first, _snake[c].second, *_blocks[0].get());
    setScore(0);
    setMap(_map);
}

void acd::Snake::_setGameOver()
{
    std::unique_ptr<ATextBlock> gameOver = std::make_unique<ATextBlock>();
    gameOver.get()->setText("GAME OVER");
    gameOver.get()->setColor(Color::BLACK);
    gameOver.get()->setBackColor(Color::RED);
    gameOver.get()->setTextPosition(13, 15);
    _map.setText("gameOver", *gameOver.get());
    _textBlocks.push_back(std::move(gameOver));
    _isGameOver = true;
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
            if (_direction != 2 && _movedOnce) {
                _direction = 0;
                _movedOnce = false;
            }
            break;
        case Input::KEY_D:
            if (_direction != 3 && _movedOnce) {
                _direction = 1;
                _movedOnce = false;
            }
            break;
        case Input::KEY_Z:
            if (_direction != 0 && _movedOnce) {
                _direction = 2;
                _movedOnce = false;
            }
            break;
        case Input::KEY_Q:
            if (_direction != 1 && _movedOnce) {
                _direction = 3;
                _movedOnce = false;
            }
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
    _movedOnce = true;
    for (std::size_t c = 0; c < _snake.size(); c++) {
        if (_snake[c].first == 0 || _snake[c].first == 30 || _snake[c].second == 0 || _snake[c].second == 30) {
            _setGameOver();
        } else {
            _map.setBlock(_snake[c].first, _snake[c].second, *_blocks[0].get());
            for (std::size_t c2 = c + 1; c2 < _snake.size(); c2++) {
                if (_snake[c].first == _snake[c2].first && _snake[c].second == _snake[c2].second) {
                    _setGameOver();
                }
            }
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

