#pragma once
#include "player.h"

class EventBlock : public Block
{
public:
    EventBlock(int position);
    virtual ~EventBlock();

    virtual void enter(Player* player);

	void checkEvent(Player* player); 

	void drink(Player* player);
	void cc(Player* player);
	void takeSubject(Player* player);
	void loseSubject(Player* player);
	void lol(Player* player);
	void eatChicken(Player* player);
	void clubActivity(Player* player);
};
