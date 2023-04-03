#include <iostream>
#include <memory>

#include "IGameModule.hpp"
#include "AGameModule.hpp"
#include "Snake.hpp"

extern "C" std::unique_ptr<acd::IGameModule> gameEntryPoint()
{
    return std::make_unique<acd::Snake>();
}
