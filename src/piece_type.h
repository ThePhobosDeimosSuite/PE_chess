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
