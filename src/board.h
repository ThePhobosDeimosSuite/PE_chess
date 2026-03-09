#pragma once
#include "chess_constants.h"
#include "move.h"
#include <iostream>
#include <assert.h>
#include <array>

enum Tile : uint8_t
{
    Empty, // 0

    B_Pawn,   // 1
    B_Rook,   // 2
    B_Bishop, // 3
    B_Knight, // 4
    B_King,   // 5
    B_Queen,  // 6

    W_Pawn,   // 7
    W_Rook,   // 8
    W_Bishop, // 9
    W_Knight, // 10
    W_King,   // 11
    W_Queen,  // 12

    max_tile
};

std::ostream &operator<<(std::ostream &out, Tile tile);

using BoardType = std::array<Tile, Chess::BoardSize>;

namespace Settings
{
    inline constexpr BoardType STARTING_BOARD{
        B_Rook, B_Knight, B_Bishop, B_Queen, B_King, B_Bishop, B_Knight, B_Rook,
        B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn,

        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,

        W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn,
        W_Rook, W_Knight, W_Bishop, W_Queen, W_King, W_Bishop, W_Knight, W_Rook};
}

namespace Rendering
{
    void clearScreen();

    // Diplay information for each tile
    struct TileDisplay
    {
        std::string_view color{};
        std::string_view icon{};

        friend std::ostream &operator<<(std::ostream &out, const TileDisplay &tile);
    };

    inline constexpr std::array horizontalAxisChar{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    inline constexpr std::array verticalAxisChar{'1', '2', '3', '4', '5', '6', '7', '8'};
    static_assert(std::ssize(horizontalAxisChar) == Chess::RowSize);
    static_assert(std::ssize(verticalAxisChar) == Chess::RowSize);

    inline constexpr std::string_view horizontalLine{"  ------------------------"};
    inline constexpr std::string_view verticalLine{"|"};

    // Console ANSI display colors
    inline constexpr std::string_view blackTileANSIColor{"\033[33m"};
    inline constexpr std::string_view whiteTileANSIColor{"\033[34m"};
    inline constexpr std::string_view defaultANSIColor{"\033[0m"};

    inline constexpr std::array tileDisplayValue{
        TileDisplay{defaultANSIColor, "."},
        TileDisplay{blackTileANSIColor, "P"},
        TileDisplay{blackTileANSIColor, "R"},
        TileDisplay{blackTileANSIColor, "B"},
        TileDisplay{blackTileANSIColor, "N"},
        TileDisplay{blackTileANSIColor, "K"},
        TileDisplay{blackTileANSIColor, "Q"},
        TileDisplay{whiteTileANSIColor, "P"},
        TileDisplay{whiteTileANSIColor, "R"},
        TileDisplay{whiteTileANSIColor, "B"},
        TileDisplay{whiteTileANSIColor, "N"},
        TileDisplay{whiteTileANSIColor, "K"},
        TileDisplay{whiteTileANSIColor, "Q"},
    };
    static_assert(std::ssize(tileDisplayValue) == Tile::max_tile);
};

class Board
{
    BoardType m_board{};

public:
    Board(BoardType board) : m_board{board} {}

    friend std::ostream &operator<<(std::ostream &out, const Board &board);

    Tile getTile(Coordinate coordinate) const;
    void setTile(Coordinate coordinate, Tile tile);
    void movePiece(const Move &move);
};