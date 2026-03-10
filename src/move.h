#pragma once
#include "chess_constants.h"
#include <assert.h>

struct Coordinate
{
    int x;
    int y;

    Coordinate(int v_x, int v_y) : x{v_x}, y{v_y}
    {
        assert(x < Chess::RowSize && "x coordinate is out of bound");
        assert(y < Chess::RowSize && "y coordinate is out of bound");
    }
};

class Move
{
    const Coordinate m_origin;
    const Coordinate m_destination;

public:
    // Move(int originX, int originY, int destinationX, int destinationY) : m_origin{originX, originY}, m_destination{destinationX, destinationY} {}
    Move(const Coordinate &origin, const Coordinate &destination) : m_origin{origin}, m_destination{destination} {}

    const Coordinate &getOrigin() const { return m_origin; };
    const Coordinate &getDestination() const { return m_destination; };
};