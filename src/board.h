#pragma once
#include "chess_constants.h"
#include "move.h"
#include "io_utils.h"
#include "tile.h"
#include <iostream>
#include <utility>
#include <vector>
#include <assert.h>
#include <array>

using BoardType = std::array<Tile, Chess::BoardSize>;

namespace Settings
{
    inline constexpr BoardType startingBoard{
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
    // Diplay information for each tile

    inline constexpr std::array horizontalAxisChar{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    inline constexpr std::array verticalAxisChar{'1', '2', '3', '4', '5', '6', '7', '8'};
    static_assert(std::ssize(horizontalAxisChar) == Chess::RowSize);
    static_assert(std::ssize(verticalAxisChar) == Chess::RowSize);

    inline constexpr std::string_view horizontalLine{"  ------------------------"};
    inline constexpr std::string_view verticalLine{"|"};

    inline constexpr std::array tileDisplayValue{
        TileDisplay{OutputUtils::defaultANSIColor, "."},
        TileDisplay{OutputUtils::blackTileANSIColor, "P"},
        TileDisplay{OutputUtils::blackTileANSIColor, "R"},
        TileDisplay{OutputUtils::blackTileANSIColor, "B"},
        TileDisplay{OutputUtils::blackTileANSIColor, "N"},
        TileDisplay{OutputUtils::blackTileANSIColor, "K"},
        TileDisplay{OutputUtils::blackTileANSIColor, "Q"},
        TileDisplay{OutputUtils::whiteTileANSIColor, "P"},
        TileDisplay{OutputUtils::whiteTileANSIColor, "R"},
        TileDisplay{OutputUtils::whiteTileANSIColor, "B"},
        TileDisplay{OutputUtils::whiteTileANSIColor, "N"},
        TileDisplay{OutputUtils::whiteTileANSIColor, "K"},
        TileDisplay{OutputUtils::whiteTileANSIColor, "Q"},
    };
    static_assert(tileDisplayValue.size() == Tile::max_tile);
};

class Board
{
    BoardType m_board{};
    std::vector<Message> &m_messageBuffer;

public:
    Board(BoardType board, std::vector<Message> &messageBuffer) : m_board{board}, m_messageBuffer{messageBuffer} {}

    friend std::ostream &operator<<(std::ostream &out, const Board &board);

    void movePlayerPiece(const Move &move);

private:
    void movePiece(const Move &move);
    void movePiece(const Move &move, Tile originTile);
    bool isPlayerTile(Tile tile);
    Tile getTile(Coordinate coordinate) const;
    void setTile(Coordinate coordinate, Tile tile);
};