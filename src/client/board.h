#pragma once
#include "block.h"
#include "player.h"

// circular dependency
class Block;
class Player;

class Board
{
private:
    Block** blocks;
    int length;

public:
    Board();
    ~Board();
    void enter(Player* player);

    int getLength() const;
    Block* getBlock(int position) const;
};
