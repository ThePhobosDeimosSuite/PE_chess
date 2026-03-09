#include "move.h"

const Coordinate &Move::getOrigin() const
{
    return m_origin;
}

const Coordinate &Move::getDestination() const
{
    return m_destination;
}