#pragma once
#include "playerqueue.h"
#include "board.h"
#include "block.h"
#include <QObject>
#include "dice.h"


namespace LocalGameState {
    enum State {
        ROLL_DICE,
        PLAYER_MOVING,
        SELL_SUBJECT,
        JUMP_PLAYER,
        TURN_OVER,
        EVENT_DRINK,
        EVENT_TAKE_SUBJECT,
        EVENT_LOSE_SUBJECT,
        EVENT_PHOTOGENIC,
        CORNER_RETAKE_SUBJECT,
        GAME_OVER
    };
}

class LocalGame;

class LocalGame : public QObject
{
    Q_OBJECT
public slots:
    void diceEvent(Dice * m_dice);
    void blockEvent(Block * block);
    void playerEvent(Player * player);
    void boardEvent(Board * m_board);
    void generalEvent();
signals:
    void signalAll();
private:
    //MainWindow *const window;
    QTimeLine * animation_timeline;
    LocalGameState::State m_state;
    PlayerQueue *m_player_queue;
    Player *m_current_player;
    Player *winner;
    int nPlayers;
    Board *m_board;
    Dice *m_dice;
    static LocalGame * m_inst;
public:
    LocalGame();
    virtual ~LocalGame();
    static LocalGame * getInst();
    static void delInst();
    void init(Board * board,Dice * dice);
    void addPlayer(Player * player);
    int getPlayerCount();
    void turnOver();


    Dice* getDice();
    Board* getBoard();
    Player* getCurrentPlayer();
    PlayerQueue * getPlayerQueue();
    LocalGameState::State getGameState();
    void setDice(Dice * dice);
    void setBoard(Board * board);
    void setGameState(LocalGameState::State new_state);

    void debugPrintAllPlayers();
};
