#pragma once

#include <queue>
#include <player.h>

class PlayerCircularQueue {
private:
    std::queue<Player*> * playerQueue;
public:
    PlayerCircularQueue();
    ~PlayerCircularQueue();
    void push(Player * p);
    Player* next(void);
    
};
