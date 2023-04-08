/*
** EPITECH PROJECT, 2023
** arcadedevparty
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

acd::Nibbler::Nibbler()
    : AGameModule(), _map(31, 32), _isPaused(false), _direction(1), _isGameOver(false),
    _movedOnce(false), _lastUpdate(std::chrono::system_clock::now())
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
    _setMap();
    std::unique_ptr<TextBlock> score = std::make_unique<TextBlock>();
    score.get()->setText("Score: 0");
    score.get()->setColor(Color::BLACK);
    score.get()->setBackColor(Color::WHITE);
    score.get()->setTextPosition(0, 0);
    _map.setText("score", *score.get());
    _textBlocks.push_back(std::move(score));
    std::unique_ptr<TextBlock> title = std::make_unique<TextBlock>();
    title.get()->setText("N I B B L E R");
    title.get()->setColor(Color::BLACK);
    title.get()->setBackColor(Color::WHITE);
    title.get()->setTextPosition(0, 13);
    _map.setText("title", *title.get());
    _textBlocks.push_back(std::move(title));
    restart();
    setMap(_map);
}

void acd::Nibbler::_setMap()
{
    for (std::size_t x = 0; x < 31; x++) {
        _map.setBlock(x, 1, *_blocks[1].get());
        _map.setBlock(x, 31, *_blocks[1].get());
    }
    for (std::size_t y = 1; y < 32; y++) {
        _map.setBlock(0, y, *_blocks[1].get());
        _map.setBlock(30, y, *_blocks[1].get());
    }
    for (std::size_t x = 5; x < 11; x++) {
        for (std::size_t y = 5; y < 11; y++) {
            _map.setBlock(x, y, *_blocks[1].get());
        }
    }
    for (std::size_t x = 5; x < 11; x++) {
        for (std::size_t y = 20; y < 26; y++) {
            _map.setBlock(x, y, *_blocks[1].get());
        }
    }
    for (std::size_t x = 20; x < 26; x++) {
        for (std::size_t y = 5; y < 11; y++) {
            _map.setBlock(x, y, *_blocks[1].get());
        }
    }
    for (std::size_t x = 20; x < 26; x++) {
        for (std::size_t y = 20; y < 26; y++) {
            _map.setBlock(x, y, *_blocks[1].get());
        }
    }
    _nibbler = std::vector<std::pair<int, int>>();
    _nibbler.push_back(std::pair<int, int>(17, 30));
    _nibbler.push_back(std::pair<int, int>(16, 30));
    _nibbler.push_back(std::pair<int, int>(15, 30));
    _nibbler.push_back(std::pair<int, int>(14, 30));
    for (std::size_t c = 0; c < _nibbler.size(); c++)
        _map.setBlock(_nibbler[c].first, _nibbler[c].second, *_blocks[0].get());


    for (std::size_t a = 0; a < 29; a++) {
        std::size_t rx = rand() % 30;
        std::size_t ry = rand() % 30;
        if (((rx >= 5 && rx <= 10) && (ry >= 5 && ry <= 10)) ||
            ((rx >= 5 && rx <= 10) && (ry >= 20 && ry <= 25)) ||
            ((rx >= 20 && rx <= 25) && (ry >= 5 && ry <= 10)) ||
            ((rx >= 20 && rx <= 25) && (ry >= 20 && ry <= 25))) {
            a--;
            continue;
        } else {
            _map.setBlock(rx, ry, *_blocks[2].get());
            _food.push_back(std::pair<int, int>(rx, ry));
        }
    }
}

void acd::Nibbler::_setGameOver()
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

bool acd::Nibbler::_checkCollision()
{
    size_t x = _nibbler[0].first;
    size_t y = _nibbler[0].second;
    if (_direction == 0) {
        y++;
    } else if (_direction == 1) {
        x++;
    } else if (_direction == 2) {
        y--;
    } else if (_direction == 3) {
        x--;
    }
    if (x == 0 || x == 30 || y == 1 || y == 31)
        return true;
    if ((x >= 5 && x <= 10) && (y >= 5 && y <= 10))
        return true;
    if ((x >= 5 && x <= 10) && (y >= 20 && y <= 25))
        return true;
    if ((x >= 20 && x <= 25) && (y >= 5 && y <= 10))
        return true;
    if ((x >= 20 && x <= 25) && (y >= 20 && y <= 25))
        return true;
    return false;
}

void acd::Nibbler::_changeDirection()
{
    size_t x = _nibbler[0].first;
    size_t y = _nibbler[0].second;
    if (_direction == 0) {
        _direction = 1;
        if (_checkCollision()) {
            _direction = 3;
            if (_checkCollision())
                _direction = 0;
        }
    } else if (_direction == 1) {
        _direction = 2;
        if (_checkCollision()) {
            _direction = 0;
            if (_checkCollision())
                _direction = 1;
        }
    } else if (_direction == 2) {
        _direction = 3;
        if (_checkCollision()) {
            _direction = 1;
            if (_checkCollision())
                _direction = 2;
        }
    } else if (_direction == 3) {
        _direction = 0;
        if (_checkCollision()) {
            _direction = 2;
            if (_checkCollision())
                _direction = 3;
        }
    }
}

acd::updateType_t acd::Nibbler::update(acd::Input latestInput)
{
    size_t r = 0;
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
    for (std::size_t c = 0; c < _nibbler.size(); c++)
        _map.removeBlock(_nibbler[c].first, _nibbler[c].second);
    switch (_direction) {
        case 0:
            _nibbler.insert(_nibbler.begin(), std::pair<int, int>(_nibbler[0].first, _nibbler[0].second + 1));
            break;
        case 1:
            _nibbler.insert(_nibbler.begin(), std::pair<int, int>(_nibbler[0].first + 1, _nibbler[0].second));
            break;
        case 2:
            _nibbler.insert(_nibbler.begin(), std::pair<int, int>(_nibbler[0].first, _nibbler[0].second - 1));
            break;
        case 3:
            _nibbler.insert(_nibbler.begin(), std::pair<int, int>(_nibbler[0].first - 1, _nibbler[0].second));
            break;
        default:
            break;
    }
    _nibbler.pop_back();
    _movedOnce = true;
    for (std::size_t c = 0; c < _nibbler.size(); c++) {
        if (_checkCollision())
            _changeDirection();
        else {
            _map.setBlock(_nibbler[c].first, _nibbler[c].second, *_blocks[0].get());
            for (std::size_t c2 = c + 1; c2 < _nibbler.size(); c2++) {
                if (_nibbler[c].first == _nibbler[c2].first && _nibbler[c].second == _nibbler[c2].second) {
                    _setGameOver();
                }
            }
        }
    }
    for (size_t f = 0; f < 30; f++) {
        if (_nibbler[0].first == _food[f].first && _nibbler[0].second == _food[f].second) {
            _nibbler.push_back(std::pair<int, int>(_nibbler[_nibbler.size() - 1].first, _nibbler[_nibbler.size() - 1].second));
            _map.removeBlock(_food[f].first, _food[f].second);
            _food.at(f) = std::pair<int, int>(0, 0);
            setScore(getScore() + 100);
        }
    }
    _map.getText("score").setText("Score: " + std::to_string(getScore()));
    setMap(_map);
    _lastUpdate = std::chrono::system_clock::now();
    return acd::updateType_t::UPDATE_NONE;
}

void acd::Nibbler::pause()
{
    _isPaused = true;
}

void acd::Nibbler::play()
{
    _isPaused = false;
}

void acd::Nibbler::restart()
{
    _map.removeText("gameOver");
    for (std::size_t x = 1; x < 30; x++)
        for (std::size_t y = 2; y < 31; y++)
            _map.removeBlock(x, y);
    _setMap();
    setScore(0);
    _map.getText("score").setText("Score: " + std::to_string(getScore()));
    setMap(_map);
}



