#include "localgame.h"

LocalGame::LocalGame()
{
    playerQueue = new Queue<Player>();
}

LocalGame::~LocalGame()
{
    delete playerQueue;
}
