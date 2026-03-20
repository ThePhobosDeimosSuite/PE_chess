#pragma once
#include "tile.h"
#include <iostream>
#include <assert.h>

class Move
{
    Tile m_origin{};
    Tile m_destination{};

public:
    // Move(int originX, int originY, int destinationX, int destinationY) : m_origin{originX, originY}, m_destination{destinationX, destinationY} {}
    Move() = default;
    Move(const Tile &origin, const Tile &destination) : m_origin{origin}, m_destination{destination} {}

    const Tile &getOrigin() const { return m_origin; };
    const Tile &getDestination() const { return m_destination; };

    bool operator==(const Move &move) const
    {
        return m_origin == move.getOrigin() && m_destination == move.getDestination();
    }

    // debug
    friend std::ostream &operator<<(std::ostream &out, const Move &move)
    {
        out << "Origin: (" << move.getOrigin().x << ", " << move.getOrigin().y << ") Destination: (" << move.getDestination().x << ", " << move.getDestination().y << ")\n";
        return out;
    }
};