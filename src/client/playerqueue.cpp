#include "playerqueue.h"

// Constructor & Destructor
PlayerQueue::PlayerQueue()
{
    playerQueue = new std::queue<Player*>();
    size = 0;
}

PlayerQueue::~PlayerQueue()
{
    delete[] playerQueue;
}


// Methods
void PlayerQueue::push(Player * p){
    playerQueue->push(p);
}

Player * PlayerQueue::next(){
    if(playerQueue->empty())
        return NULL;
    Player * ret = playerQueue->front();
    playerQueue->pop();
    playerQueue->push(ret);
    return ret;
}

int PlayerQueue::getSize(){
    return size;
}
