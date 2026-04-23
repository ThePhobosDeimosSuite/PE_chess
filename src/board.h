#pragma once
#include "move.h"
#include "tile.h"
#include "message.h"
#include "chess_constants.h"
#include "piece_type.h"
#include <iostream>
#include <utility>
#include <vector>
#include <assert.h>
#include <array>

using BoardType = std::array<PieceType, Chess::BoardSize>;

namespace Chess
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

class Board
{
    BoardType m_board{};

public:
    Board(BoardType board) : m_board{board} {}

    friend std::ostream &operator<<(std::ostream &out, const Board &board);

    const PieceType &getPieceType(const Tile &tile) const;
    PieceColor getPieceColor(const Tile &tile) const;
    void movePiece(Move &move);
    void unMovePiece(const Move &move);
    bool isPlayerTile(const Tile &tile) const;
    bool isGameOver() const;
    bool hasPlayerWon() const;
    bool hasCPUWon() const;

    void forEachTile(const auto &fn) const
    {
        for (int i{0}; i < Chess::RowSize; i++)
        {
            for (int j{0}; j < Chess::RowSize; j++)
            {
                fn(Tile{i, j});
            }
        }
    }

private:
    void setPieceType(const Tile &tile, PieceType pieceType);
};