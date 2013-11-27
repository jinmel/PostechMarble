#pragma once
#include <queue>
#include "player.h"

class PlayerQueue {
private:
    std::queue<Player*> * playerQueue;
    int size;

public:
    PlayerQueue();
    ~PlayerQueue();
    void push(Player * p);
    Player* next(void);
    
};
