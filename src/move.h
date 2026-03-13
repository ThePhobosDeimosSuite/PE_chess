#pragma once
#include "tile.h"
#include <assert.h>

class Move
{
    const Tile m_origin;
    const Tile m_destination;

public:
    // Move(int originX, int originY, int destinationX, int destinationY) : m_origin{originX, originY}, m_destination{destinationX, destinationY} {}
    Move(const Tile &origin, const Tile &destination) : m_origin{origin}, m_destination{destination} {}

    const Tile &getOrigin() const { return m_origin; };
    const Tile &getDestination() const { return m_destination; };
};