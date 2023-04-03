#include <iostream>
#include <memory>

#include "IGraphicModule.hpp"
#include "AGraphicModule.hpp"

extern "C" std::unique_ptr<acd::IGraphicModule> graphicEntryPoint()
{
    return nullptr;
}
