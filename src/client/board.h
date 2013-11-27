#pragma once
#include "player.h"
#include "block.h"

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
