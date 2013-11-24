#pragma once
#include "block.h"

// circular dependency
class Board;
class Player;

class Block
{
public:
    enum CornerType
    {
        DORMITORY,
        CALLTAXI,
        BREAKSEMESTER,
        PLURALMAJOR
    };
    int position;

public:
    Block();
    virtual ~Block();

    void setPosition(int position);
    virtual void enter(Player* player) = 0;
};

