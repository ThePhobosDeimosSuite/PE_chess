#include <iostream>

enum Tile : uint8_t
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

std::ostream &operator<<(std::ostream &out, Tile tile);

struct TileDisplay
{
    std::string_view color{};
    std::string_view icon{};

    friend std::ostream &operator<<(std::ostream &out, const TileDisplay &tile);
};