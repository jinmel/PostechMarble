#include "localgame.h"
#include "dice.h"
#include "board.h"
#include <iostream>
#include <QDebug>
#include <QtGlobal>

using namespace std;
using namespace LocalGameState;

LocalGame::LocalGame(){
    m_state = ROLL_DICE;
    player_queue = new PlayerQueue;
}

//Singleton methods
LocalGame * LocalGame::m_inst = NULL;

LocalGame * LocalGame::getInst(){
    if(m_inst == NULL)
        m_inst = new LocalGame;
    return m_inst;
}

void LocalGame::delInst(){
    if(m_inst != NULL){
        delete m_inst;
        m_inst = NULL;
    }
}

void LocalGame::addPlayer(Player *new_player){
    player_queue->push(new_player);
}

void LocalGame::init(Board * board, Dice * dice){
    m_current_player = player_queue->next();
    Q_CHECK_PTR(m_current_player);
    m_board = board;
    m_dice = dice;
}

Board* LocalGame::getBoard(){
    return m_board;
}

void LocalGame::setBoard(Board *board){
    m_board = board;
}

Dice* LocalGame::getDice(){
    return m_dice;
}

void LocalGame::setDice(Dice * dice){
    m_dice = dice;
}

Player* LocalGame::getCurrentPlayer(){
    return m_current_player;
}

LocalGameState::State LocalGame::getCurrentGameState(){
    return m_state;
}

void LocalGame::setCurrentGameState(State new_state){
    m_state = new_state;
}

void LocalGame::diceEvent(Dice * dice){
    if(m_state == ROLL_DICE){
        m_current_player->walkBy(dice->getValue());
        Block * current_block = m_board->getBlock(m_current_player->getPosition());
        current_block->enter(m_current_player);
    }
}

void LocalGame::turnOver(){
    //switch current player to next player and change state
    m_current_player = player_queue->next();
    m_state = ROLL_DICE;
}

void LocalGame::blockEvent(Block *block){
    if(m_state == JUMP_PLAYER){

    }
}

void LocalGame::playerEvent(Player *player){

}

void LocalGame::boardEvent(Board *board){

}
