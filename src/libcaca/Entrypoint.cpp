#include <iostream>
#include <memory>

#include "IGraphicModule.hpp"
#include "AGraphicModule.hpp"
#include "Libcaca.hpp"

extern "C" std::unique_ptr<acd::IGraphicModule> graphicEntryPoint()
{
    return std::make_unique<acd::Libcaca>();
}
