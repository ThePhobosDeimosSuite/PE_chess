#pragma once
#include "move.h"
#include <string_view>
#include <string>

namespace InputUtils
{
    inline constexpr int invalidCoordinate{-1};
    Move getMoveInputFromUser();

    Coordinate axisCharToCoordinate(char x, char y);
}

namespace OutputUtils
{
    // Console ANSI display colors
    inline constexpr std::string_view errorANSIColor{"\033[31m"};
    inline constexpr std::string_view successANSIColor{"\033[32m"};
    inline constexpr std::string_view blackTileANSIColor{"\033[33m"};
    inline constexpr std::string_view whiteTileANSIColor{"\033[34m"};
    inline constexpr std::string_view defaultANSIColor{"\033[0m"};

    void clearScreen();

    std::pair<char, char> coordinateToAxisChar(Coordinate coordinate);
}

struct Message
{
    enum Type
    {
        Alert,
        Success
    };

    std::string text;
    Type type;

    friend std::ostream &operator<<(std::ostream &out, Message &message);
};