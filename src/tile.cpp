#include "tile.h"
#include "io_utils.h"

std::ostream &operator<<(std::ostream &out, const TileDisplay &tile)
{
    out << tile.color << tile.icon << OutputUtils::defaultANSIColor;
    return out;
}