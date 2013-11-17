#pragma once
#include "playerqueue.h"

PlayerCircularQueue::PlayerCircularQueue() {
    
}

PlayerCircularQueue::~PlayerCircularQueue(){
    for(int i = 0; i < size ; i ++ ){
        Player * p = playerQueue->pop();
        delete p;
    }
}

void PlayerCircularQueue::push(Player * p){
    playerQueue->push(p);
}

Player * PlayerCircularQueue::next(){
    Player * ret = queue.pop();
    playerQueue->push(ret);
    return ret;
}
