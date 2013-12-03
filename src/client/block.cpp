#include "block.h"

// Constructor & Destructor
Block::Block(QGameItem * parent) : QGameItem(parent)
{
    // dummy
    position = -1;
    value = 0;
    block_type = BlockType::NONE;
}


Block::~Block()
{
}


// Methods
int Block::getValue() const
{
    return value;
}


BlockType::Type Block::getType() const
{
    return block_type;
}


void Block::setPosition(int position)
{
    this->position = position;
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "block:" << position;
}

void Block::setPos(const QPointF &pos){
    this->pos = QPointF(pos);
    QGameItem::setPos(pos);
}
