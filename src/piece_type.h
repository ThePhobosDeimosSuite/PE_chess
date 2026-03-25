#pragma once
#include <iostream>
#include <format>
#include <array>

enum class PieceColor
{
    Black,
    White,
    None,
    max_color
};

enum PieceType : uint8_t
{
    Empty, // 0

    B_Pawn,   // 1
    B_Rook,   // 2
    B_Bishop, // 3
    B_Knight, // 4
    B_King,   // 5
    B_Queen,  // 6

    W_Pawn,   // 7
    W_Rook,   // 8
    W_Bishop, // 9
    W_Knight, // 10
    W_King,   // 11
    W_Queen,  // 12

    max_tile
};
std::ostream &
operator<<(std::ostream &out, PieceType tile);

namespace Piece
{
    inline constexpr int getPieceValue(PieceType pieceType)
    {
        switch (pieceType)
        {
        case W_Bishop:
        case B_Bishop:
            return 330;
        case W_King:
        case B_King:
            return 0;
        case W_Rook:
        case B_Rook:
            return 500;
        case W_Knight:
        case B_Knight:
            return 320;
        case W_Pawn:
        case B_Pawn:
            return 100;
        case W_Queen:
        case B_Queen:
            return 900;
        default:
            return 0;
        }
    }
    inline constexpr PieceColor getPieceColor(PieceType pieceType)
    {
        if (pieceType >= B_Pawn && pieceType <= B_Queen)
        {
            return PieceColor::Black;
        }

        if (pieceType >= W_Pawn && pieceType <= W_Queen)
        {
            return PieceColor::White;
        }

        return PieceColor::None;
    };
}
