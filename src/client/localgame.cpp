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
    Player * currentPlayer = playerQueue->next();
    do {
        Dice::getInst()->roll();
        currentPlayer->moveTo(Dice::getInst()->getValue() % board->getLength());
        Block * curBlock = board->getBlock(Dice::getInst()->getValue());
        curBlock->enter(currentPlayer);
        if(currentPlayer->checkWinStatus()) {
            break;
        } 
        if (!Dice::getInst()->isDouble())
            currentPlayer = playerQueue->next();
    } while(1); // fix this inf. loop
}


void LocalGame::printStats(){
    //requires qt
    return;
}
