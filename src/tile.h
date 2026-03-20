#pragma once
#include "chess_constants.h"
#include <assert.h>
#include <utility>

namespace TileUtils
{
    inline constexpr int invalidTile{-1};
    inline constexpr int maxTile{7};
}

struct Tile
{
    int x{TileUtils::invalidTile};
    int y{TileUtils::invalidTile};

    Tile() = default;
    Tile(int v_x, int v_y) : x{v_x}, y{v_y}
    {
        assert(x <= TileUtils::maxTile && "x coordinate is out of bound");
        assert(y <= TileUtils::maxTile && "y coordinate is out of bound");
    }

    Tile(char horizontalAxisChar, char verticalAxisChar)
    {
        for (int i{0}; i < Chess::horizontalAxisChar.size(); i++)
        {
            if (Chess::horizontalAxisChar[i] == horizontalAxisChar)
            {
                x = i;
                break;
            }
        }

        for (int i{0}; i < Chess::verticalAxisChar.size(); i++)
        {
            if (Chess::verticalAxisChar[i] == verticalAxisChar)
            {
                y = i;
                break;
            }
        }
    }

    std::pair<char, char> toCoordinate() const
    {
        char horizontal_char{Chess::horizontalAxisChar[this->x]};
        char vertical_char{Chess::verticalAxisChar[this->y]};

        return {horizontal_char, vertical_char};
    }

    bool operator==(const Tile &tile) const
    {
        return x == tile.x && y == tile.y;
    }
};
