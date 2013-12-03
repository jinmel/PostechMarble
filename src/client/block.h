#pragma once
#include "types.h"
#include "player.h"
#include "qgameitem.h"


class Player;

class Block : public QGameItem
{
protected:
    int position;
    BlockType::Type block_type;
    QPointF coord;
public:
    Block(QGameItem * parent);
    virtual ~Block();
    BlockType::Type getType() const;
    void setPosition(int position);
    void setPos(const QPointF &coord);
    virtual void enter(Player* player) = 0;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

