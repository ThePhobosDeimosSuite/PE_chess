#include "board.h"
#include <iomanip>
#include <format>
#include <iostream>

Tile Board::getTile(Coordinate coordinate) const
{
    return m_board[coordinate.y * Chess::RowSize + coordinate.x];
}

void Board::setTile(Coordinate coordinate, Tile tile)
{
    m_board[coordinate.y * Chess::RowSize + coordinate.x] = tile;
}

void Board::movePiece(const Move &move)
{
    auto originTile{this->getTile(move.getOrigin())};
    movePiece(move, originTile);
}

void Board::movePiece(const Move &move, Tile originTile)
{
    setTile(move.getDestination(), originTile);
    setTile(move.getOrigin(), Tile::Empty);
}

bool Board::isPlayerTile(Tile tile)
{
    return tile >= Tile::W_Pawn && tile <= Tile::W_Queen;
}

void Board::movePlayerPiece(const Move &move)
{
    auto originTile{this->getTile(move.getOrigin())};
    auto originAxisChar{move.getOrigin().toAxisChar()};

    if (!isPlayerTile(originTile))
    {
        m_messageBuffer.emplace_back(std::format("Tile ({}, {}) is not one of your piece",
                                                 originAxisChar.first,
                                                 originAxisChar.second),
                                     Message::Alert);
        return;
    }

    // TODO check move conditions

    movePiece(move, originTile);

    // TODO check is destination tile is an enemy, if so print a special message

    auto destinationAxisChar{move.getDestination().toAxisChar()};
    m_messageBuffer.emplace_back(std::format("Tile ({}, {}) moved to ({}, {})",
                                             originAxisChar.first,
                                             originAxisChar.second,
                                             destinationAxisChar.first,
                                             destinationAxisChar.second),
                                 Message::Success);
}