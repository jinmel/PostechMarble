#pragma once
#include <queue>

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
