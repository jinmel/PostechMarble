#pragma once
#include "playerqueue.h"
#include "board.h"
#include "block.h"
#include <QObject>

class LocalGame;

class LocalGame : public QObject
{
    Q_OBJECT
public slots:
    void diceRolled(int value,bool is_double);
signals:
    //signal to energy label
    void energyChanged(int player_num,int energy);
    //signal to status bar
    void activatePlayer(int player_num);
    //signal to player pieces
    void playerMoved(int block_num);
private:
    PlayerQueue * playerQueue;
    Board * board;
    Player * curPlayer;
    static LocalGame* m_inst;
    LocalGame();
public:
    virtual ~LocalGame();
    //singleton static methods
    static LocalGame *getInst();
    static void delInst();
};
