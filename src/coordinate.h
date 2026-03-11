#pragma once
#include "chess_constants.h"
#include <assert.h>
#include <utility>

namespace CoordinateUtils
{
    inline constexpr int invalidCoordinate{-1};
}

struct Coordinate
{
    int x{CoordinateUtils::invalidCoordinate};
    int y{CoordinateUtils::invalidCoordinate};

    Coordinate(int v_x, int v_y) : x{v_x}, y{v_y}
    {
        assert(x < Chess::RowSize && "x coordinate is out of bound");
        assert(y < Chess::RowSize && "y coordinate is out of bound");
    }

    Coordinate(char horizontalAxisChar, char verticalAxisChar)
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

    std::pair<char, char> toAxisChar() const
    {
        char horizontal_char{Chess::horizontalAxisChar[this->x]};
        char vertical_char{Chess::verticalAxisChar[this->y]};

        return {horizontal_char, vertical_char};
    }
};
