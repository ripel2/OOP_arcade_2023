#include <iostream>

#include "IGraphicModule.hpp"
#include "AGraphicModule.hpp"
#include "GraphicSdl.hpp"

extern "C" std::unique_ptr<acd::IGraphicModule> graphicEntryPoint()
{
    return std::make_unique<acd::GraphicSdl>();
}
