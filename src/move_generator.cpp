#include "move_generator.h"
#include "chess_constants.h"

bool isTileInPlayingSpace(int x, int y)
{
    return x >= 0 && x <= TileUtils::maxTile && y >= 0 && y <= TileUtils::maxTile;
}

template <std::size_t SIZE>
std::vector<Move> MoveGenerator::generateDirectionMove(const Board &board, const Tile &originTile, PieceColor originPieceColor,
                                                       const std::array<std::pair<int, int>, SIZE> &moveDirections)
{
    std::vector<Move> moves{};

    for (auto [dx, dy] : moveDirections)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        while (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{board.getPieceColor(destinationTile)};
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
std::vector<Move> MoveGenerator::generateOffetMove(const Board &board, const Tile &originTile, PieceColor originPieceColor,
                                                   const std::array<std::pair<int, int>, SIZE> &moveOffsets)
{
    std::vector<Move> moves{};

    for (auto [dx, dy] : moveOffsets)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        if (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{board.getPieceColor(destinationTile)};
            if (destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
            }
        }
    }
    return moves;
};

template <std::size_t SIZE1, std::size_t SIZE2>
std::vector<Move> MoveGenerator::generatePawnMove(const Board &board, const Tile &originTile, PieceColor originPieceColor,
                                                  const std::array<std::pair<int, int>, SIZE1> &moveOffsets,
                                                  const std::array<std::pair<int, int>, SIZE2> &attackOffsets)
{
    std::vector<Move> moves{};
    for (auto [dx, dy] : moveOffsets)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        if (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            PieceColor destinationPieceColor{board.getPieceColor(destinationTile)};
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
            PieceColor destinationPieceColor{board.getPieceColor(destinationTile)};
            if (destinationPieceColor != PieceColor::None && destinationPieceColor != originPieceColor)
            {
                moves.emplace_back(originTile, destinationTile);
            }
        }
    }

    return moves;
}

std::vector<Move>
MoveGenerator::getAvailableMoves(const Board &board, const Tile &tile)
{
    auto pieceType{board.getPieceType(tile)};
    auto pieceColor{Piece::getPieceColor(pieceType)};

    switch (pieceType)
    {
    case PieceType::B_Rook:
    case PieceType::W_Rook:
        return generateDirectionMove(board, tile, pieceColor, MoveGenerator::rookDirections);
        break;
    case PieceType::B_Bishop:
    case PieceType::W_Bishop:
        return generateDirectionMove(board, tile, pieceColor, MoveGenerator::bishopDirections);
        break;
    case PieceType ::B_Queen:
    case PieceType::W_Queen:
        return generateDirectionMove(board, tile, pieceColor, MoveGenerator::queenDirections);
        break;
    case PieceType::B_Knight:
    case PieceType::W_Knight:
        return generateOffetMove(board, tile, pieceColor, MoveGenerator::knightOffsets);
        break;
    case PieceType::B_King:
    case PieceType::W_King:
        return generateOffetMove(board, tile, pieceColor, MoveGenerator::kingOffsets);
        break;
    case PieceType::B_Pawn:
        return generatePawnMove(board, tile, pieceColor, MoveGenerator::blackPawnOffsets, MoveGenerator::blackPawnAttackOffsets);
        break;
    case PieceType::W_Pawn:
        return generatePawnMove(board, tile, pieceColor, MoveGenerator::whitePawnOffsets, MoveGenerator::whitePawnAttackOffsets);
        break;
    default:
        return {};
    }
}
