#include "input_utils.h"
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

    std::string getMoveInput(std::string_view prompt)
    {
        while (true)
        {
            std::cout << prompt;
            std::string input{};
            std::cin >> input;

            if (isInputValid(input))
            {
                return input;
            }

            std::cout << "Invalid input\n";
        }
    }

    // TODO check if can't find value in Rendering::array
    Coordinate moveInputToCoordinate(std::string_view input)
    {
        int x{};
        int y{};
        for (int i{0}; i < Rendering::horizontalAxisChar.size(); i++)
        {
            if (Rendering::horizontalAxisChar[i] == input[0])
            {
                x = i;
                break;
            }
        }

        for (int i{0}; i < Rendering::verticalAxisChar.size(); i++)
        {
            if (Rendering::verticalAxisChar[i] == input[1])
            {
                y = i;
                break;
            }
        }
        return {x, y};
    }

    Move getMoveInputFromUser()
    {
        auto originMoveInput{getMoveInput("Enter the origin coordinate: ")};
        auto destinationMoveInput{getMoveInput("Enter the destination coordinate: ")};

        return Move(moveInputToCoordinate(originMoveInput), moveInputToCoordinate(destinationMoveInput));
    }
}