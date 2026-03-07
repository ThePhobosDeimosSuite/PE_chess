#include "board.h"
#include <iomanip>
#include <iostream>

namespace Rendering
{
    std::ostream &operator<<(std::ostream &out, const Rendering::TileDisplay &tile)
    {
        out << tile.color << tile.icon << Rendering::DEFAULT_ANSI_COLOR;
        return out;
    }
}

std::ostream &operator<<(std::ostream &out, Tile tile)
{
    out << Rendering::TILE_DISPLAY_VALUE[tile];
    return out;
}

void printHorizontalAxis(std::ostream &out)
{
    out << "  ";
    for (int i{0}; i < std::ssize(Rendering::HORIZONTAL_AXIS_CHAR); i++)
    {
        out << " " << Rendering::HORIZONTAL_AXIS_CHAR[i] << " ";
    }
}

void printHorizontalLine(std::ostream &out)
{
    out << Rendering::HORIZONTAL_LINE;
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
    printHorizontalAxis(out);
    out << '\n';
    printHorizontalLine(out);
    out << '\n';

    for (int i{0}; i < Settings::BOARD_SIZE; i++)
    {
        if (i % Settings::ROW_SIZE == 0)
        {
            if (i != 0)
            {
                out << Rendering::VERTICAL_LINE;
                // this will implicit cast correctly right?
                out << Rendering::VERTICAL_AXIS_CHAR[i / Settings::ROW_SIZE - 1];

                out << '\n';
            }

            out << Rendering::VERTICAL_AXIS_CHAR[i / Settings::ROW_SIZE];
            out << Rendering::VERTICAL_LINE;
        }

        // printing space instead of setw() because setw() doesn't work with the color concat when printing Tile
        out << " " << board.m_board[i] << " ";
    }

    out << Rendering::VERTICAL_LINE;
    out << Rendering::VERTICAL_AXIS_CHAR[Settings::ROW_SIZE - 1];

    out << '\n';
    printHorizontalLine(out);
    out << '\n';
    printHorizontalAxis(out);

    return out;
}