#include "move_generator.h"
#include "chess_constants.h"

bool constexpr isTileInPlayingSpace(int x, int y)
{
    return x >= 0 && x <= TileUtils::maxTile && y >= 0 && y <= TileUtils::maxTile;
}

template <std::size_t SIZE>
void MoveGenerator::generateDirectionMove(std::array<Move, MoveGenerator::maxMoves> &moveList,
                                          const Board &board, const Tile &originTile, PieceColor originPieceColor,
                                          const std::array<std::pair<int, int>, SIZE> &moveDirections)
{
    int count{0};

    for (auto [dx, dy] : moveDirections)
    {
        int x{originTile.x + dx};
        int y{originTile.y + dy};

        while (isTileInPlayingSpace(x, y))
        {
            Tile destinationTile{x, y};
            // TODO store colors in a board array to get color faster?
            PieceColor destinationPieceColor{board.getPieceColor(destinationTile)};
            if (destinationPieceColor == PieceColor::None)
            {
                moveList[count++] = Move{originTile, destinationTile};
            }
            else if (destinationPieceColor != originPieceColor)
            {
                moveList[count++] = Move{originTile, destinationTile};
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
}

template <std::size_t SIZE>
void MoveGenerator::generateOffetMove(std::array<Move, MoveGenerator::maxMoves> &moveList,
                                      const Board &board, const Tile &originTile, PieceColor originPieceColor,
                                      const std::array<std::pair<int, int>, SIZE> &moveOffsets)
{
    int count{0};

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
                moveList[count++] = Move{originTile, destinationTile};
            }
        }
    }
};

template <std::size_t SIZE1, std::size_t SIZE2>
void MoveGenerator::generatePawnMove(std::array<Move, MoveGenerator::maxMoves> &moveList,
                                     const Board &board, const Tile &originTile, PieceColor originPieceColor,
                                     const std::array<std::pair<int, int>, SIZE1> &moveOffsets,
                                     const std::array<std::pair<int, int>, SIZE2> &attackOffsets)
{
    int count{0};

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
                moveList[count++] = Move{originTile, destinationTile};
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
                moveList[count++] = Move{originTile, destinationTile};
            }
        }
    }
}

void MoveGenerator::getAvailableMoves(std::array<Move, MoveGenerator::maxMoves> &moveList,
                                      const Board &board, const Tile &tile)
{
    auto pieceType{board.getPieceType(tile)};
    auto pieceColor{Piece::getPieceColor(pieceType)};

    switch (pieceType)
    {
    case PieceType::B_Rook:
    case PieceType::W_Rook:
        generateDirectionMove(moveList, board, tile, pieceColor, MoveGenerator::rookDirections);
        break;
    case PieceType::B_Bishop:
    case PieceType::W_Bishop:
        generateDirectionMove(moveList, board, tile, pieceColor, MoveGenerator::bishopDirections);
        break;
    case PieceType ::B_Queen:
    case PieceType::W_Queen:
        generateDirectionMove(moveList, board, tile, pieceColor, MoveGenerator::queenDirections);
        break;
    case PieceType::B_Knight:
    case PieceType::W_Knight:
        generateOffetMove(moveList, board, tile, pieceColor, MoveGenerator::knightOffsets);
        break;
    case PieceType::B_King:
    case PieceType::W_King:
        generateOffetMove(moveList, board, tile, pieceColor, MoveGenerator::kingOffsets);
        break;
    case PieceType::B_Pawn:
        generatePawnMove(moveList, board, tile, pieceColor, MoveGenerator::blackPawnOffsets, MoveGenerator::blackPawnAttackOffsets);
        break;
    case PieceType::W_Pawn:
        generatePawnMove(moveList, board, tile, pieceColor, MoveGenerator::whitePawnOffsets, MoveGenerator::whitePawnAttackOffsets);
        break;
    }
}
