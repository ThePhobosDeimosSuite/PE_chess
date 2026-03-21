#pragma once
#include <string_view>
#include <array>
namespace Chess
{
    inline constexpr int RowSize{8};
    inline constexpr int BoardSize{RowSize * RowSize};

    inline constexpr std::array horizontalAxisChar{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    inline constexpr std::array verticalAxisChar{'1', '2', '3', '4', '5', '6', '7', '8'};
    static_assert(std::ssize(horizontalAxisChar) == Chess::RowSize);
    static_assert(std::ssize(verticalAxisChar) == Chess::RowSize);
};

namespace ANSIColor
{
    // Console ANSI display colors
    inline constexpr std::string_view error{"\033[31m"};
    inline constexpr std::string_view success{"\033[32m"};
    inline constexpr std::string_view info{"\033[35m"};
    inline constexpr std::string_view blackTile{"\033[33m"};
    inline constexpr std::string_view whiteTile{"\033[34m"};
    inline constexpr std::string_view defaultColor{"\033[0m"};
}