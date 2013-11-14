#ifndef EVENTBLOCK_H
#define EVENTBLOCK_H

class EventBlock : public Block
{
public:
    EventBlock();
	~EventBlock();

	void drink(Player* player);
	void cc(Player* player);
	void takeSubject(Player* player);
	void loseSubject(Player* player);
	void lol(Player* player);
	void eatChicken(Player* player);
	void clubActivity(Player* player);
};

#endif // EVENTBLOCK_H
