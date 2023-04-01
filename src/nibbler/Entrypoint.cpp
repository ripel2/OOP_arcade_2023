#include <iostream>

#include "IGameModule.hpp"
#include "AGameModule.hpp"

extern "C" std::unique_ptr<acd::IGameModule> gameEntryPoint()
{
    return nullptr;
}
