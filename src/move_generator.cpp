#include "move_generator.h"
#include "chess_constants.h"

std::vector<Move> MoveGenerator::getAvailableMoves(Tile tile) const
{
    auto pieceType{m_board.getPieceType(tile)};
    auto pieceColor{Piece::getPieceColor(pieceType)};

    switch (pieceType)
    {
    case PieceType::B_Rook:
    case PieceType::W_Rook:
        return getAvailableRookMoves(tile, pieceColor);
        break;
    }

    return {};
}

// bool isEnemyTile()
// {

// }

// bool isTileEmpty()
// {

// }

std::vector<Move> MoveGenerator::getAvailableRookMoves(Tile originTile, PieceColor originPieceColor) const
{
    std::vector<Move> moves{};

    // Check x+
    if (originTile.x <= TileUtils::maxTile - 1)
    {
        for (int i{originTile.x + 1}; i <= TileUtils::maxTile; i++)
        {
            Tile destinationTile{i, originTile.y};
            PieceType destinationPieceType{m_board.getPieceType(destinationTile)};
            PieceColor destinationPieceColor{Piece::getPieceColor(destinationPieceType)};
            if (destinationPieceColor == PieceColor::None)
            {
                moves.emplace_back(originTile, destinationTile);
            }
            else if (destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
                break;
            }
            else
            {
                break;
            }
        }
    }

    // Check x-
    if (originTile.x > 0)
    {
        for (int i{originTile.x - 1}; i >= 0; i--)
        {
            Tile destinationTile{i, originTile.y};
            PieceType destinationPieceType{m_board.getPieceType(destinationTile)};
            PieceColor destinationPieceColor{Piece::getPieceColor(destinationPieceType)};
            if (destinationPieceColor == PieceColor::None)
            {
                moves.emplace_back(originTile, destinationTile);
            }
            else if (destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
                break;
            }
            else
            {
                break;
            }
        }
    }

    // Check y+
    if (originTile.y <= TileUtils::maxTile - 1)
    {
        for (int i{originTile.y + 1}; i <= TileUtils::maxTile; i++)
        {
            Tile destinationTile{originTile.x, i};
            PieceType destinationPieceType{m_board.getPieceType(destinationTile)};
            PieceColor destinationPieceColor{Piece::getPieceColor(destinationPieceType)};
            if (destinationPieceColor == PieceColor::None)
            {
                moves.emplace_back(originTile, destinationTile);
            }
            else if (destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
                break;
            }
            else
            {
                break;
            }
        }
    }

    // Check y-
    if (originTile.y > 0)
    {
        for (int i{originTile.y - 1}; i >= 0; i--)
        {
            Tile destinationTile{originTile.x, i};
            PieceType destinationPieceType{m_board.getPieceType(destinationTile)};
            PieceColor destinationPieceColor{Piece::getPieceColor(destinationPieceType)};
            if (destinationPieceColor == PieceColor::None)
            {
                moves.emplace_back(originTile, destinationTile);
            }
            else if (destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
                break;
            }
            else
            {
                break;
            }
        }
    }

    return moves;
}