#pragma once
#include <QQueue>
#include "player.h"
#include <QList>
#include <QVector>

class PlayerQueue {
private:
    QQueue<Player*> * queue;
public:
    PlayerQueue();
    ~PlayerQueue();
    void push(Player * p);
    Player* next(void);
    int getSize();
    QVector<Player*> toVector() const;
};
