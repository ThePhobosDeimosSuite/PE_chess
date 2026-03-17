#pragma once
#include "move.h"
#include "piece_type.h"
#include "board.h"
#include "message.h"
#include <string_view>
#include <array>

namespace Rendering
{
    void clearScreen();

    inline constexpr std::string_view horizontalLine{"  ------------------------"};
    inline constexpr std::string_view verticalLine{"|"};

    struct TileDisplay
    {
        std::string_view color{};
        std::string_view icon{};

        friend std::ostream &operator<<(std::ostream &out, const TileDisplay &tile);
    };

    // TODO use getPieceColor to get the color of a tile
    // Order is defined in Tile.h
    inline constexpr std::array tileDisplayValue{
        TileDisplay{ANSIColor::defaultColor, "."},
        TileDisplay{ANSIColor::blackTile, "P"},
        TileDisplay{ANSIColor::blackTile, "R"},
        TileDisplay{ANSIColor::blackTile, "B"},
        TileDisplay{ANSIColor::blackTile, "N"},
        TileDisplay{ANSIColor::blackTile, "K"},
        TileDisplay{ANSIColor::blackTile, "Q"},
        TileDisplay{ANSIColor::whiteTile, "P"},
        TileDisplay{ANSIColor::whiteTile, "R"},
        TileDisplay{ANSIColor::whiteTile, "B"},
        TileDisplay{ANSIColor::whiteTile, "N"},
        TileDisplay{ANSIColor::whiteTile, "K"},
        TileDisplay{ANSIColor::whiteTile, "Q"},
    };
    static_assert(tileDisplayValue.size() == PieceType::max_tile);
}