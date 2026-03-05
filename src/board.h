#include <iostream>
#include <array>

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

namespace Settings
{
    inline constexpr int ROW_SIZE{8};
    inline constexpr int BOARD_SIZE{ROW_SIZE * ROW_SIZE};
};

using BoardType = std::array<Tile, Settings::BOARD_SIZE>;

namespace Settings
{
    inline constexpr BoardType STARTING_BOARD{
        B_Rook, B_Knight, B_Bishop, B_Queen, B_King, B_Bishop, B_Knight, B_Rook,
        B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn,

        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,

        W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn,
        W_Rook, W_Knight, W_Bishop, W_Queen, W_King, W_Bishop, W_Knight, W_Rook};
}

namespace Rendering
{
    // Diplay information for each tile
    struct TileDisplay
    {
        std::string_view color{};
        std::string_view icon{};

        friend std::ostream &operator<<(std::ostream &out, const TileDisplay &tile);
    };

    // Console ANSI display colors
    inline constexpr std::string_view BLACK_TILE_ANSI_COLOR{"\033[33m"};
    inline constexpr std::string_view WHITE_TILE_ANSI_COLOR{"\033[34m"};
    inline constexpr std::string_view DEFAULT_ANSI_COLOR{"\033[0m"};

    inline constexpr std::array TILE_DISPLAY_VALUE{
        TileDisplay{DEFAULT_ANSI_COLOR, " "},
        TileDisplay{BLACK_TILE_ANSI_COLOR, "P"},
        TileDisplay{BLACK_TILE_ANSI_COLOR, "R"},
        TileDisplay{BLACK_TILE_ANSI_COLOR, "B"},
        TileDisplay{BLACK_TILE_ANSI_COLOR, "N"},
        TileDisplay{BLACK_TILE_ANSI_COLOR, "K"},
        TileDisplay{BLACK_TILE_ANSI_COLOR, "Q"},
        TileDisplay{WHITE_TILE_ANSI_COLOR, "P"},
        TileDisplay{WHITE_TILE_ANSI_COLOR, "R"},
        TileDisplay{WHITE_TILE_ANSI_COLOR, "B"},
        TileDisplay{WHITE_TILE_ANSI_COLOR, "N"},
        TileDisplay{WHITE_TILE_ANSI_COLOR, "K"},
        TileDisplay{WHITE_TILE_ANSI_COLOR, "Q"},
    };
    static_assert(std::ssize(TILE_DISPLAY_VALUE) == Tile::max_tile);
};

class Board
{
    BoardType m_board{};

public:
    Board(BoardType board) : m_board{board} {}

    friend std::ostream &operator<<(std::ostream &out, const Board &board);
};