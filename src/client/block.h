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
public:
    Block();
    virtual ~Block();
    virtual void enter(Player* player);
};

