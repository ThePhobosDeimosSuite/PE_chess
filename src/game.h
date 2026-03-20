#include "board.h"
#include "rendering.h"
#include "input.h"
#include "message.h"
#include "move_generator.h"
#include <vector>

class Game
{
    std::vector<Message> m_messageBuffer{};
    Board m_board;

public:
    Game() : m_board{Chess::startingBoard} {};

    void run();

private:
    void printUI();
};