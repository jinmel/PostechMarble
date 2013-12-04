#pragma once
#include "types.h"
#include "player.h"
#include "qgameitem.h"


class Player;
class Block;

class Block : public QGameItem
{
    Q_OBJECT
protected:
    int position;
    BlockType::Type block_type;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:
    Block(QGameItem * parent);
    virtual ~Block();
    BlockType::Type getType() const;
    void setPosition(int position);
    int getPosition();
    virtual void enter(Player* player) = 0;
signals:
    void blockClicked(Block * block);
};

