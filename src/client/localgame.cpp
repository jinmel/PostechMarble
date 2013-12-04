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
    if(m_inst == NULL){
        m_inst = new LocalGame;
    }

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
    nPlayers++;
    emit new_player->disable();
    connect(new_player,SIGNAL(playerArrived(Player*)),this,SLOT(playerEvent(Player*)));
}

void LocalGame::init(Board * board, Dice * dice){
    m_current_player = player_queue->next();
    Q_CHECK_PTR(m_current_player);
    emit m_current_player->activate();
    m_board = board;
    m_dice = dice;
    nPlayers = 0;
    connect(m_dice,SIGNAL(diceRolled(Dice*)),this,SLOT(diceEvent(Dice*)));
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

LocalGameState::State LocalGame::getGameState(){
    return m_state;
}

void LocalGame::setGameState(State new_state){
    m_state = new_state;
}

void LocalGame::diceEvent(Dice * dice){
    qDebug() << "dice event caught by localgame";
    if(m_state == ROLL_DICE){
        if(m_current_player->isMobile()){
            m_current_player->walkBy(dice->getValue());
            m_state = PLAYER_MOVING;
        }
        else{
            if(dice->isDouble()){
                m_current_player->setMobile(true);
                m_current_player->walkBy(dice->getValue());
                m_state = PLAYER_MOVING;
            }
            else{
                turnOver();
            }
        }
    }
}

void LocalGame::turnOver(){
    //switch current player to next player and change state
    if(m_current_player->checkWinStatus()){
        //TODO: need to emit signal to notify gameover
        winner = m_current_player;
        qDebug() << "winner! player:" << m_current_player->getId();
        m_state = GAME_OVER;
        return;
    }
    if(m_current_player->isBankrupt()){
        nPlayers--;
        if(nPlayers == 1) {
            winner = player_queue->next();
            m_state = GAME_OVER;
            return;
        }
    }
    //should never happen
    Q_ASSERT(nPlayers != 1);
    //update current Player if dice is not double
    emit m_current_player->disable();
    if(!Dice::getInst()->isDouble()){
        do {
            m_current_player = player_queue->next();
        } while(m_current_player->isBankrupt());
    }
    emit m_current_player->activate();
    m_state = ROLL_DICE;
}

void LocalGame::blockEvent(Block *block){
    if(m_state == JUMP_PLAYER){
        m_current_player->jumpTo(block->getPosition());
    }
}

void LocalGame::playerEvent(Player *player){
    qDebug() << "signal emmited by Player" << player->getId();
    if(m_state == PLAYER_MOVING){
        qDebug() << "Player in block!";
        int position = player->getPosition();
        Block * cur_block = m_board->getBlock(position);
        cur_block->enter(player);
    }
}

void LocalGame::boardEvent(Board *board){

}
