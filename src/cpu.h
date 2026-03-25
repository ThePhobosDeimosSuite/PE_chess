#pragma once
#include "move.h"
#include "move_generator.h"
#include "board.h"
#include <array>

namespace CPU
{
    inline constexpr int minmaxDepth{4};
    Move generateBestMoves(Board &board);
}