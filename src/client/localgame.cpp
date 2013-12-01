#include "localgame.h"
#include "dice.h"
#include "board.h"
#include <iostream>
#include <QDebug>

using namespace std;

//initialize static member instance
LocalGame* LocalGame::m_inst = NULL;

// Constructor & Destructor
LocalGame::LocalGame()
{
    qDebug() << "LocalGame Initialized" << endl;
}

LocalGame::~LocalGame()
{
    delete playerQueue;
    delete board;
}

LocalGame * LocalGame::getInst(){
    if(!m_inst)
        m_inst = new LocalGame;
    return m_inst;
}

void LocalGame::delInst(){
    delete m_inst;
}

void LocalGame::diceRolled(int value, bool is_double){
    //the most important method in this project.
    //main routine for the game

}
