#pragma once
#include "block.h"
#include "player.h"

// circular dependency
class Block;
class Player;

class Board
{
private:
    Block** boards;
public:
    Board();
    virtual ~Board();
    virtual void enter(Player* player);
};
