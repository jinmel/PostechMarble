#pragma once
#include "playerqueue.h"
#include "board.h"
#include "block.h"
//#include "gamerecord.h"

class LocalGame
{
private:
    PlayerQueue * playerQueue;
    Board * board;
public:
    LocalGame(int num_players=2);
    ~LocalGame();
    Player * currentPlayer();
    Board * board();
    Block * block();

};
