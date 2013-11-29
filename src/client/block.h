#pragma once
#include "types.h"
#include "player.h"

// circular dependency
class Player;

class Block
{
protected:
    int position;
    int value;
    BlockType::Type block_type;

public:
    Block();
    virtual ~Block();
    int getValue() const;
    BlockType::Type getType() const;
    void setPosition(int position);
    virtual void enter(Player* player) = 0;
};

