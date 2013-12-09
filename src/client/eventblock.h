#pragma once
#include "player.h"
#include "block.h"
#include "types.h"
#include <QGraphicsScene>
#include <QQueue>


class EventBlock : public Block
{
private:
    QQueue<int> eventqueue;
public:
    EventBlock(QGameItem * parent, QGraphicsScene * scene, MainWindow * window);
    virtual ~EventBlock();

    virtual void enter(Player* player);

    void checkEvent(Player* player,QGraphicsScene * scene, MainWindow * window);

    void drink(Player* player);
    void cc(Player* player);
    void takeSubject(Player* player);
    void loseSubject(Player* player);
    void lol(Player* player);
    void eatChicken(Player* player);
    void photoGenic(QGraphicsScene * scene, MainWindow * window);
};
