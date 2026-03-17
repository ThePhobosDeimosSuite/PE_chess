#include "board.h"
#include <iomanip>
#include <format>
#include <iostream>

PieceType Board::getPieceType(const Tile &tile) const
{
    return m_board[tile.y * Chess::RowSize + tile.x];
}

void Board::setPieceType(Tile tile, PieceType pieceType)
{
    m_board[tile.y * Chess::RowSize + tile.x] = pieceType;
}

void Board::movePiece(const Move &move)
{
    auto originTile{this->getPieceType(move.getOrigin())};
    movePiece(move, originTile);
}

void Board::movePiece(const Move &move, PieceType originPieceType)
{
    setPieceType(move.getDestination(), originPieceType);
    setPieceType(move.getOrigin(), PieceType::Empty);
}

bool Board::isPlayerTile(const Tile &tile) const
{
    auto pieceType{getPieceType(tile)};
    return Piece::getPieceColor(pieceType) == PieceColor::White;
}

PieceColor Board::getPieceColor(const Tile &tile) const
{
    return Piece::getPieceColor(getPieceType(tile));
}

bool Board::hasPlayerWon() const
{
    for (PieceType pieceType : m_board)
    {
        if (pieceType == B_King)
        {
            return false;
        }
    }
    return true;
}

bool Board::hasCPUWon() const
{
    for (PieceType pieceType : m_board)
    {
        if (pieceType == W_King)
        {
            return false;
        }
    }
    return true;
}
