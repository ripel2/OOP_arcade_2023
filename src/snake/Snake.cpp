/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL: Ubuntu]
** File description:
** Snake
*/

#include "Snake.hpp"

acd::Snake::Snake()
    : AGameModule(), _map(31, 32), _isPaused(false), _direction(0), _isGameOver(false),
    _movedOnce(false), _food(0, 0), _lastUpdate(std::chrono::system_clock::now())
{
    _isPaused = false;
    _blocks = std::vector<std::unique_ptr<Block>>();
    _textBlocks = std::vector<std::unique_ptr<TextBlock>>();
    std::unique_ptr<Block> snakeBlock = std::make_unique<Block>();
    char blockchars[2] = {' ', ' '};
    snakeBlock.get()->loadTexturesNcurses(Color::WHITE, Color::BLUE, blockchars);
    _blocks.push_back(std::move(snakeBlock));
    std::unique_ptr<Block> wallBlock = std::make_unique<Block>();
    char wallchars[2] = {' ', ' '};
    wallBlock.get()->loadTexturesNcurses(Color::WHITE, Color::RED, wallchars);
    _blocks.push_back(std::move(wallBlock));
    std::unique_ptr<Block> foodBlock = std::make_unique<Block>();
    char foodchars[2] = {'O', 'O'};
    foodBlock.get()->loadTexturesNcurses(Color::WHITE, Color::GREEN, foodchars);
    _blocks.push_back(std::move(foodBlock));
    for (std::size_t x = 0; x < 31; x++) {
        _map.setBlock(x, 1, *_blocks[1].get());
        _map.setBlock(x, 31, *_blocks[1].get());
    }
    for (std::size_t y = 1; y < 32; y++) {
        _map.setBlock(0, y, *_blocks[1].get());
        _map.setBlock(30, y, *_blocks[1].get());
    }
    std::unique_ptr<TextBlock> score = std::make_unique<TextBlock>();
    score.get()->setText("Score: 0");
    score.get()->setColor(Color::BLACK);
    score.get()->setBackColor(Color::WHITE);
    score.get()->setTextPosition(0, 0);
    _map.setText("score", *score.get());
    _textBlocks.push_back(std::move(score));
    std::unique_ptr<TextBlock> title = std::make_unique<TextBlock>();
    title.get()->setText("S N A K E");
    title.get()->setColor(Color::BLACK);
    title.get()->setBackColor(Color::WHITE);
    title.get()->setTextPosition(0, 13);
    _map.setText("title", *title.get());
    _textBlocks.push_back(std::move(title));
    restart();
    setMap(_map);
}

void acd::Snake::_setGameOver()
{
    std::unique_ptr<TextBlock> gameOver = std::make_unique<TextBlock>();
    gameOver.get()->setText("GAME  OVER");
    gameOver.get()->setColor(Color::BLACK);
    gameOver.get()->setBackColor(Color::RED);
    gameOver.get()->setTextPosition(15, 13);
    _map.setText("gameOver", *gameOver.get());
    _textBlocks.push_back(std::move(gameOver));
    _isGameOver = true;
}

acd::updateType_t acd::Snake::update(Input latestInput)
{
    if (latestInput == Input::KEY__P) {
        _isPaused = !_isPaused;
    }
    if (latestInput == Input::KEY__R) {
        restart();
        _isGameOver = false;
        _isPaused = false;
    }
    if (_isPaused || _isGameOver)
        return acd::updateType_t::UPDATE_NONE;
    switch (latestInput) {
        case Input::KEY__S:
            if (_direction != 2 && _movedOnce) {
                _direction = 0;
                _movedOnce = false;
            }
            break;
        case Input::KEY__D:
            if (_direction != 3 && _movedOnce) {
                _direction = 1;
                _movedOnce = false;
            }
            break;
        case Input::KEY__Z:
            if (_direction != 0 && _movedOnce) {
                _direction = 2;
                _movedOnce = false;
            }
            break;
        case Input::KEY__Q:
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
        if (_snake[c].first == 0 || _snake[c].first == 30 || _snake[c].second == 1 || _snake[c].second == 31) {
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
    if (_snake[0].first == _food.first && _snake[0].second == _food.second) {
        _snake.push_back(std::pair<int, int>(_snake[_snake.size() - 1].first, _snake[_snake.size() - 1].second));
        _map.removeBlock(_food.first, _food.second);
        _food = std::pair<int, int>(rand() % 29 + 1, rand() % 29 + 2);
        _map.setBlock(_food.first, _food.second, *_blocks[2].get());
        setScore(getScore() + 1);
    }
    _map.getText("score").setText("Score: " + std::to_string(getScore()));
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
    _map.removeText("gameOver");
    for (std::size_t x = 1; x < 30; x++)
        for (std::size_t y = 2; y < 31; y++)
            _map.removeBlock(x, y);
    _snake = std::vector<std::pair<int, int>>();
    _direction = 0;
    _snake.push_back(std::pair<int, int>(15, 15));
    _snake.push_back(std::pair<int, int>(15, 14));
    _snake.push_back(std::pair<int, int>(15, 13));
    _snake.push_back(std::pair<int, int>(15, 12));
    _food = std::pair<int, int>(15, 22);
    _map.setBlock(_food.first, _food.second, *_blocks[2].get());
    for (std::size_t c = 0; c < _snake.size(); c++)
        _map.setBlock(_snake[c].first, _snake[c].second, *_blocks[0].get());
    setScore(0);
    _map.getText("score").setText("Score: " + std::to_string(getScore()));
    setMap(_map);
}
