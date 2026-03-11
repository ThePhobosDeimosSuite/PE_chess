#include "input.h"
#include "chess_constants.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>

namespace Input
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
                Coordinate coordinate{input[0], input[1]};
                if (coordinate.x != CoordinateUtils::invalidCoordinate && coordinate.y != CoordinateUtils::invalidCoordinate)
                {
                    return coordinate;
                }
            }

            std::cout << ANSIColor::error << "Invalid input\n"
                      << ANSIColor::defaultColor;
        }
    }

    Move getMoveInputFromUser()
    {
        auto originMoveInput{getCoordinateInputFromUser("Enter the origin coordinate: ")};
        auto destinationMoveInput{getCoordinateInputFromUser("Enter the destination coordinate: ")};

        return Move(originMoveInput, destinationMoveInput);
    }
}
