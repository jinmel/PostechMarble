#pragma once
#include "player.h"
#include "block.h"
#include "qgameitem.h"
#include "mainwindow.h"
#include <QPointF>

class Board : public QGameItem
{
    Q_OBJECT
private:
    Block** blocks;
    int length;
public:
    Board(QGraphicsScene * scene,MainWindow * window);
    virtual ~Board();
    void enter(Player* player);
    int getLength() const;
    Block* getBlock(int position) const;
public slots:
    void diceRolled(int dice,bool is_double);
};

namespace BlockCoords {
    extern const int corner_w;
    extern const int corner_h;
    extern const int hblock_w;
//extern const int hblock_h = 114; //not used
//extern const int vblock_w = 142; //not used
    extern const int vblock_h;
    extern QPointF block_coord[32];
    extern QPointF corner_coord[4];
}

