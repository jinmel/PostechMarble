#include "localgame.h"
#include "dice.h"
#include "board.h"
#include <iostream>
#include <QDebug>

using namespace std;

// Constructor & Destructor
LocalGame::LocalGame(int num_players)
{
    playerQueue = new PlayerQueue();
    for (int i = 0; i < num_players; i ++)
        playerQueue->push(new Player);
    
    board = new Board();

    qDebug() << "LocalGame Initialized" << endl;
}


LocalGame::~LocalGame()
{
    delete playerQueue;
}

// Methods
void LocalGame::play(){

}


void LocalGame::printStats(){
    //requires qt
    return;
}
