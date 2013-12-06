#include "playerqueue.h"

// Constructor & Destructor
PlayerQueue::PlayerQueue()
{
    queue = new QQueue<Player*>;
}

PlayerQueue::~PlayerQueue()
{
    delete[] queue;
}

// Methods
void PlayerQueue::push(Player * p){
    queue->enqueue(p);
}

Player * PlayerQueue::next(){
    if(queue->empty())
        return NULL;
    Player * ret = queue->front();
    queue->pop_front();
    queue->enqueue(ret);
    return ret;
}

int PlayerQueue::getSize(){
    return queue->length();
}

QVector<Player*> PlayerQueue::toVector() const{
    return queue->toVector();
}
