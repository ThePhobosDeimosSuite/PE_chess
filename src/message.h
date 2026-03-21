#pragma once
#include <ostream>
#include <string>

struct Message
{
    enum Type
    {
        Alert,
        Success,
        Info
    };

    std::string text;
    Type type;

    friend std::ostream &operator<<(std::ostream &out, Message &message);
};