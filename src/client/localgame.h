#pragma once
#include "playerqueue.h"

class LocalGame
{
private:
    PlayerCircularQueue * playerQueue;
    Board * board;
public:
    LocalGame(int num_players=2);
    ~LocalGame();
    void play();
    void printStats();
};
