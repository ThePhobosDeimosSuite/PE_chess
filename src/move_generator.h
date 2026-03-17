#pragma once
#include "board.h"
#include "tile.h"
#include "move.h"
#include "utils.h"
#include <vector>
#include <array>

namespace PieceMovement
{
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
}
class MoveGenerator
{
    const Board &m_board;

public:
    MoveGenerator(const Board &board) : m_board{board} {}

    std::vector<Move> getAvailableMoves(Tile tile) const;

private:
    template <std::size_t SIZE>
    std::vector<Move> generateDirectionMove(Tile originTile, PieceColor originPieceColor,
                                            const std::array<std::pair<int, int>, SIZE> &moveDirections) const;
    template <std::size_t SIZE>
    std::vector<Move> generateOffetMove(Tile originTile, PieceColor originPieceColor,
                                        const std::array<std::pair<int, int>, SIZE> &moveOffsets) const;
    template <std::size_t SIZE1, std::size_t SIZE2>
    std::vector<Move> generatePawnMove(Tile originTile, PieceColor originPieceColor,
                                       const std::array<std::pair<int, int>, SIZE1> &moveOffsets,
                                       const std::array<std::pair<int, int>, SIZE2> &attackOffsets) const;
};