#include "move_generator.h"
#include "chess_constants.h"

bool isTileInPlayingSpace(int x, int y)
{
    return x >= 0 && x <= TileUtils::maxTile && y >= 0 && y <= TileUtils::maxTile;
}

template <std::size_t SIZE>
std::vector<Move> MoveGenerator::generateDirectionMove(Tile originTile, PieceColor originPieceColor,
                                                       const std::array<std::pair<int, int>, SIZE> &moveDirections) const
{
    std::vector<Move> moves{};

    for (auto [dx, dy] : moveDirections)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        while (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{m_board.getPieceColor(destinationTile)};
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

            x += dx;
            y += dy;
        }
    }

    return moves;
}

template <std::size_t SIZE>
std::vector<Move> MoveGenerator::generateOffetMove(Tile originTile, PieceColor originPieceColor,
                                                   const std::array<std::pair<int, int>, SIZE> &moveOffsets) const
{
    std::vector<Move> moves{};

    for (auto [dx, dy] : moveOffsets)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        if (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{m_board.getPieceColor(destinationTile)};
            if (destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
            }
        }
    }
    return moves;
};

template <std::size_t SIZE1, std::size_t SIZE2>
std::vector<Move> MoveGenerator::generatePawnMove(Tile originTile, PieceColor originPieceColor,
                                                  const std::array<std::pair<int, int>, SIZE1> &moveOffsets,
                                                  const std::array<std::pair<int, int>, SIZE2> &attackOffsets) const
{
    std::vector<Move> moves{};
    for (auto [dx, dy] : moveOffsets)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        if (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{m_board.getPieceColor(destinationTile)};
            if (destinationPieceColor == PieceColor::None)
            {
                moves.emplace_back(originTile, destinationTile);
            }
        }
    }

    for (auto [dx, dy] : attackOffsets)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        if (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{m_board.getPieceColor(destinationTile)};
            if (destinationPieceColor != PieceColor::None && destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
            }
        }
    }

    return moves;
}

std::vector<Move>
MoveGenerator::getAvailableMoves(Tile tile) const
{
    auto pieceType{m_board.getPieceType(tile)};
    auto pieceColor{Piece::getPieceColor(pieceType)};

    switch (pieceType)
    {
    case PieceType::B_Rook:
    case PieceType::W_Rook:
        return generateDirectionMove(tile, pieceColor, PieceMovement::rookDirections);
        break;
    case PieceType::B_Bishop:
    case PieceType::W_Bishop:
        return generateDirectionMove(tile, pieceColor, PieceMovement::bishopDirections);
        break;
    case PieceType ::B_Queen:
    case PieceType::W_Queen:
        return generateDirectionMove(tile, pieceColor, PieceMovement::queenDirections);
        break;
    case PieceType::B_Knight:
    case PieceType::W_Knight:
        return generateOffetMove(tile, pieceColor, PieceMovement::knightOffsets);
        break;
    case PieceType::B_King:
    case PieceType::W_King:
        return generateOffetMove(tile, pieceColor, PieceMovement::kingOffsets);
        break;
    case PieceType::B_Pawn:
        return generatePawnMove(tile, pieceColor, PieceMovement::blackPawnOffsets, PieceMovement::blackPawnAttackOffsets);
        break;
    case PieceType::W_Pawn:
        return generatePawnMove(tile, pieceColor, PieceMovement::whitePawnOffsets, PieceMovement::whitePawnAttackOffsets);
        break;
    default:
        return {};
    }
}
