#include "rendering.h"
#include <ostream>

void printHorizontalAxis(std::ostream &out)
{
    out << "  ";
    for (int i{0}; i < std::ssize(Chess::horizontalAxisChar); i++)
    {
        out << " " << Chess::horizontalAxisChar[i] << " ";
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
                out << Chess::verticalAxisChar[i / Chess::RowSize - 1];
                out << '\n';
            }

            out << Chess::verticalAxisChar[i / Chess::RowSize];
            out << Rendering::verticalLine;
        }

        // printing space instead of setw() because setw() doesn't work with the color concat when printing Tile
        out << " " << board.m_board[i] << " ";
    }

    out << Rendering::verticalLine;
    out << Chess::verticalAxisChar[Chess::RowSize - 1];

    out << '\n';
    printHorizontalLine(out);
    out << '\n';
    printHorizontalAxis(out);

    return out;
}

std::ostream &operator<<(std::ostream &out, PieceType tile)
{
    out << Rendering::tileDisplayValue[tile];
    return out;
}

namespace Rendering
{
    std::ostream &operator<<(std::ostream &out, const TileDisplay &tile)
    {
        out << tile.color << tile.icon << ANSIColor::defaultColor;
        return out;
    }

    void clearScreen()
    {
        std::cout << "\x1B[2J\x1B[H" << ANSIColor::defaultColor;
    }
}

std::ostream &operator<<(std::ostream &out, Message &message)
{
    switch (message.type)
    {
    case Message::Alert:
        out << ANSIColor::error << message.text << ANSIColor::defaultColor;
        break;
    case Message::Success:
        out << ANSIColor::success << message.text << ANSIColor::defaultColor;
    }

    return out;
}