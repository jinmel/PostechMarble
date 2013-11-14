#pragma once

#include <player.h>

PlayerCircularQueue::PlayerCircularQueue() {
    
}

PlayerCircularQueue::~PlayerCircularQueue(){
    for(int i = 0; i < size ; i ++ ){
        Player * p = queue.pop();
        delete p;
    }
}

void PlayerCircularQueue::push(Player * p){
    queue.push(p);
}

Player * PlayerCircularQueue::next(){
    Player * ret = queue.pop();
    queue.push(ret);
    return ret;
}
