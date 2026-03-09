#include "board.h"
#include <iomanip>
#include <iostream>

namespace Rendering
{
    void clearScreen()
    {
        std::cout << "\x1B[2J\x1B[H";
    }

    std::ostream &operator<<(std::ostream &out, const Rendering::TileDisplay &tile)
    {
        out << tile.color << tile.icon << Rendering::defaultANSIColor;
        return out;
    }
}

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
    setTile(move.getDestination(), originTile);
    setTile(move.getOrigin(), Tile::Empty);
}