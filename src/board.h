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
    std::vector<Message> &m_messageBuffer;

public:
    Board(BoardType board, std::vector<Message> &messageBuffer) : m_board{board}, m_messageBuffer{messageBuffer} {}

    friend std::ostream &operator<<(std::ostream &out, const Board &board);

    void movePlayerPiece(const Move &move);

private:
    void movePiece(const Move &move);
    void movePiece(const Move &move, PieceType originTile);
    bool isPlayerTile(PieceType tile);
    PieceType getTile(Tile coordinate) const;
    void setTile(Tile coordinate, PieceType tile);
};