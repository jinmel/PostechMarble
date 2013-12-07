#pragma once
#include <QGraphicsScene>
#include "player.h"
#include "../mainwindow.h"
#include "../qgameitem.h"

class GameoverScene : public QGraphicsScene
{
    Q_OBJECT
private:
    bool moving;
    static Player *winner;
    MainWindow* window;
    QGameItem *background;
    QGameItem *credit_button;
    QGameItem *player_pos;
    QGameItem *winner_statement;

    void setupGameover();

public:
    static void setWinner(Player* winner);
    GameoverScene(qreal x=0, qreal y=0, qreal width=1280,
                  qreal height=720,
                  QObject* parent = 0);
    ~GameoverScene();

};
