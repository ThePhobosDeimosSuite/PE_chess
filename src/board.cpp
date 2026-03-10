#include "board.h"
#include "io_utils.h"
#include <iomanip>
#include <format>
#include <iostream>

std::ostream &operator<<(std::ostream &out, Tile tile)
{
    out << Rendering::tileDisplayValue[tile];
    return out;
}

void printHorizontalAxis(std::ostream &out)
{
    out << "  ";
    for (int i{0}; i < std::ssize(Rendering::horizontalAxisChar); i++)
    {
        out << " " << Rendering::horizontalAxisChar[i] << " ";
    }
}

void printHorizontalLine(std::ostream &out)
{
    out << Rendering::horizontalLine;
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
    printHorizontalAxis(out);
    out << '\n';
    printHorizontalLine(out);
    out << '\n';

    for (int i{0}; i < Chess::BoardSize; i++)
    {
        if (i % Chess::RowSize == 0)
        {
            if (i != 0)
            {
                out << Rendering::verticalLine;
                // this will implicit cast correctly right?
                out << Rendering::verticalAxisChar[i / Chess::RowSize - 1];

                out << '\n';
            }

            out << Rendering::verticalAxisChar[i / Chess::RowSize];
            out << Rendering::verticalLine;
        }

        // printing space instead of setw() because setw() doesn't work with the color concat when printing Tile
        out << " " << board.m_board[i] << " ";
    }

    out << Rendering::verticalLine;
    out << Rendering::verticalAxisChar[Chess::RowSize - 1];

    out << '\n';
    printHorizontalLine(out);
    out << '\n';
    printHorizontalAxis(out);

    return out;
}

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
    auto originAxisChar{OutputUtils::coordinateToAxisChar(move.getOrigin())};

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

    auto destinationAxisChar{OutputUtils::coordinateToAxisChar(move.getDestination())};
    m_messageBuffer.emplace_back(std::format("Tile ({}, {}) moved to ({}, {})",
                                             originAxisChar.first,
                                             originAxisChar.second,
                                             destinationAxisChar.first,
                                             destinationAxisChar.second),
                                 Message::Success);
}