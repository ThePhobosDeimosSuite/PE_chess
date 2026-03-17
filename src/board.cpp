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

// void Board::movePlayerPiece(const Move &move)
// {
//     auto originTile{this->getPieceType(move.getOrigin())};
//     auto originCoordinate{move.getOrigin().toCoordinate()};

//     if (!isPlayerTile(originTile))
//     {
//         m_messageBuffer.emplace_back(std::format("Tile ({}, {}) is not one of your piece",
//                                                  originCoordinate.first,
//                                                  originCoordinate.second),
//                                      Message::Alert);
//         return;
//     }

//     // TODO check move conditions
//     auto availableMoves{getAvailableMoves(move.getOrigin())};

//     movePiece(move, originTile);

//     // TODO check is destination tile is an enemy, if so print a special message

//     auto destinationCoordinate{move.getDestination().toCoordinate()};
// }