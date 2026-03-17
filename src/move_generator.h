#pragma once
#include "board.h"
#include "tile.h"
#include "move.h"
#include <vector>

class MoveGenerator
{
    const Board &m_board;

public:
    MoveGenerator(const Board &board) : m_board{board} {}

    std::vector<Move> getAvailableMoves(Tile tile) const;

private:
    std::vector<Move> getAvailableRookMoves(Tile tile, PieceColor pieceColor) const;
};