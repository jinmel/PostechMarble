#pragma once
#include "Player.h"
#include "Block.h"
#include<string.h>

class GameRecord
{
private:
    string data;
    Board * board;
    PlayerQueue * player_queue;
public:
    GameRecord(Board * board,PlayerQueue * player_queue);
    GameRecord();
    bool save(string filename);
    
};
