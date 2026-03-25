#include "board.h"
#include <iomanip>
#include <format>
#include <iostream>

const PieceType &Board::getPieceType(const Tile &tile) const
{
    return m_board[tile.y * Chess::RowSize + tile.x];
}

void Board::setPieceType(const Tile &tile, PieceType pieceType)
{
    m_board[tile.y * Chess::RowSize + tile.x] = pieceType;
}

void Board::movePiece(Move &move)
{
    move.setCapturedPiece(this->getPieceType(move.getDestination()));
    setPieceType(move.getDestination(), this->getPieceType(move.getOrigin()));
    setPieceType(move.getOrigin(), PieceType::Empty);
}

void Board::unMovePiece(const Move &move)
{
    setPieceType(move.getOrigin(), this->getPieceType(move.getDestination()));
    setPieceType(move.getDestination(), move.getCapturedPiece());
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

bool Board::isGameOver() const
{
    for (PieceType pieceType : m_board)
    {
        if (pieceType == B_King || pieceType == W_King)
        {
            return false;
        }
    }
    return true;
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
