#include "io_utils.h"
#include "board.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>

namespace InputUtils
{

    void removeSpaces(std::string &str)
    {
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
    }

    bool isInputValid(std::string &input)
    {
        removeSpaces(input);

        if (input.length() != 2)
        {
            return false;
        }

        return isalpha(input[0]) && std::isdigit(input[1]);
    }

    Coordinate getCoordinateInputFromUser(std::string_view prompt)
    {
        while (true)
        {
            std::cout << prompt;
            std::string input{};
            std::cin >> input;

            if (isInputValid(input))
            {
                auto coordinate{axisCharToCoordinate(input[0], input[1])};
                if (coordinate.x != InputUtils::invalidCoordinate && coordinate.y != InputUtils::invalidCoordinate)
                {
                    return coordinate;
                }
            }

            std::cout << OutputUtils::errorANSIColor << "Invalid input\n"
                      << OutputUtils::defaultANSIColor;
        }
    }

    Move getMoveInputFromUser()
    {
        auto originMoveInput{getCoordinateInputFromUser("Enter the origin coordinate: ")};
        auto destinationMoveInput{getCoordinateInputFromUser("Enter the destination coordinate: ")};

        return Move(originMoveInput, destinationMoveInput);
    }
    Coordinate axisCharToCoordinate(char horizontal_char, char vertical_char)
    {
        int x{InputUtils::invalidCoordinate};
        int y{InputUtils::invalidCoordinate};

        for (int i{0}; i < Rendering::horizontalAxisChar.size(); i++)
        {
            if (Rendering::horizontalAxisChar[i] == horizontal_char)
            {
                x = i;
                break;
            }
        }

        for (int i{0}; i < Rendering::verticalAxisChar.size(); i++)
        {
            if (Rendering::verticalAxisChar[i] == vertical_char)
            {
                y = i;
                break;
            }
        }

        return {x, y};
    }
}

namespace OutputUtils
{
    void clearScreen()
    {
        std::cout << "\x1B[2J\x1B[H" << OutputUtils::defaultANSIColor;
    }

    std::pair<char, char> coordinateToAxisChar(Coordinate coordinate)
    {
        char horizontal_char{Rendering::horizontalAxisChar[coordinate.x]};
        char vertical_char{Rendering::verticalAxisChar[coordinate.y]};

        return {horizontal_char, vertical_char};
    }
}

std::ostream &operator<<(std::ostream &out, Message &message)
{
    switch (message.type)
    {
    case Message::Alert:
        out << OutputUtils::errorANSIColor << message.text << OutputUtils::defaultANSIColor;
        break;
    case Message::Success:
        out << OutputUtils::successANSIColor << message.text << OutputUtils::defaultANSIColor;
    }

    return out;
}