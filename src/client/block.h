#pragma once
#include "player.h"

// circular dependency
class Player;

class Block
{
public:
    enum BlockType
    {
        Subject, Corner, Event, Friday
    };

protected:
    int position;
    int value;
    BlockType block_type;

public:
    Block();
    virtual ~Block();

    BlockType getType() const;
    void setPosition(int position);
    virtual void enter(Player* player) = 0;
};

