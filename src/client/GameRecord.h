#pragma once
#include "player.h"
#include "block.h"
#include "playerqueue.h"
#include <string>

using namespace std;

class GameRecord
{
private:
    string data;
    Board * board;
    PlayerQueue * player_queue;

public:
    GameRecord(Board * board, PlayerQueue * player_queue);
    GameRecord();
    bool save(string filename);
    
};
