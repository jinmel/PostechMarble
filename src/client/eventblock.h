#pragma once
#include "player.h"
#include "block.h"
#include "types.h"

class EventBlock : public Block
{
public:
    EventBlock();
    virtual ~EventBlock();

    virtual void enter(Player* player);

    void checkEvent(Player* player); 

    void drink(Player* player);
    void cc(Player* player);
    void takeSubject(Player* player);
    void loseSubject(Player* player);
    void lol(Player* player);
    void eatChicken(Player* player);
};
