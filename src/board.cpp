#include "board.h"

namespace Rendering
{
    std::ostream &operator<<(std::ostream &out, const Rendering::TileDisplay &tile)
    {
        out << tile.color << tile.icon;

        return out;
    }
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
    for (int i{0}; i < Settings::BOARD_SIZE; i++)
    {
        if (i % Settings::ROW_SIZE == 0)
        {
            out << '\n';
        }

        // FIX THIS, it's horrible
        // TODO overload the enum printing
        auto tile{Rendering::TILE_DISPLAY_VALUE[board.m_board[i]]};
        out << tile;
    }
    return out;
}