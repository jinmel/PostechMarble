#pragma once
#include "player.h"
#include "block.h"
#include "qgameitem.h"
#include "mainwindow.h"

class Board : public QGameItem
{
private:
    Block** blocks;
    int length;
public:
    Board(QGraphicsScene * scene,MainWindow * window);
    virtual ~Board();
    void enter(Player* player);
    int getLength() const;
    Block* getBlock(int position) const;
};
