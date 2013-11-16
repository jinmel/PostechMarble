#include "localgame.h"
#include "dice.h"
#include "board.h"
#include <iostream>

using namespace std;

LocalGame::LocalGame(int num_players)
{
    playerQueue = new PlayerCircularQueue();
    for (int i = 0; i < num_players; i ++)
        playerQueue.push(new Player);
    
    board = new Board();
}

LocalGame::~LocalGame()
{
    delete playerQueue;
}

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
