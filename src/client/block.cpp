#include "block.h"

// Constructor & Destructor
Block::Block(QGameItem * parent) : QGameItem(parent)
{
    // dummy
    position = -1;
    block_type = BlockType::NONE;
}


Block::~Block()
{
}

BlockType::Type Block::getType() const
{
    return block_type;
}


void Block::setPosition(int position)
{
    this->position = position;
}

int Block::getPosition(){
    return position;
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "block:" << position;
}
