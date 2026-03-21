#pragma once
#include "board.h"
#include "tile.h"
#include "move.h"
#include "utils.h"
#include <array>
namespace MoveGenerator
{
    constexpr int maxMoves{256};

    constexpr std::array<std::pair<int, int>, 4> rookDirections{
        {{1, 0},
         {-1, 0},
         {0, 1},
         {0, -1}}};
    constexpr std::array<std::pair<int, int>, 4> bishopDirections{
        {{1, 1},
         {-1, 1},
         {1, -1},
         {-1, -1}}};
    constexpr auto queenDirections{Utils::concat(rookDirections, bishopDirections)};

    constexpr std::array<std::pair<int, int>, 8> kingOffsets{
        {{1, 0},
         {-1, 0},
         {0, 1},
         {0, -1},
         {1, 1},
         {-1, 1},
         {1, -1},
         {-1, -1}}};
    constexpr std::array<std::pair<int, int>, 8> knightOffsets{
        {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}}};
    constexpr std::array<std::pair<int, int>, 2> whitePawnAttackOffsets{
        {{1, -1},
         {-1, -1}}};
    constexpr std::array<std::pair<int, int>, 2> blackPawnAttackOffsets{
        {{1, 1},
         {-1, 1}}};
    constexpr std::array<std::pair<int, int>, 1> whitePawnOffsets{{{0, -1}}};
    constexpr std::array<std::pair<int, int>, 1> blackPawnOffsets{{{0, 1}}};

    void getAvailableMoves(std::array<Move, MoveGenerator::maxMoves> &moveList, const Board &board, PieceColor color);

    void getAvailableMoves(std::array<Move, MoveGenerator::maxMoves> &moveList, int &count, const Board &board, const Tile &tile);

    template <std::size_t SIZE>
    void generateDirectionMove(std::array<Move, MoveGenerator::maxMoves> &moveList,
                               int &count,
                               const Board &board, const Tile &originTile, PieceColor originPieceColor,
                               const std::array<std::pair<int, int>, SIZE> &moveDirections);
    template <std::size_t SIZE>
    void generateOffetMove(std::array<Move, MoveGenerator::maxMoves> &moveList,
                           int &count,
                           const Board &board, const Tile &originTile, PieceColor originPieceColor,
                           const std::array<std::pair<int, int>, SIZE> &moveOffsets);
    template <std::size_t SIZE1, std::size_t SIZE2>
    void generatePawnMove(std::array<Move, MoveGenerator::maxMoves> &moveList,
                          int &count,
                          const Board &board, const Tile &originTile, PieceColor originPieceColor,
                          const std::array<std::pair<int, int>, SIZE1> &moveOffsets,
                          const std::array<std::pair<int, int>, SIZE2> &attackOffsets);
};