#include <iostream>

#include "IGraphicModule.hpp"
#include "AGraphicModule.hpp"
#include "Ncurses.hpp"

extern "C" std::unique_ptr<acd::IGraphicModule> graphicEntryPoint()
{
    return std::make_unique<acd::Ncurses>();
}
