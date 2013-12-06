#include "block.h"

// Constructor & Destructor
Block::Block(QGameItem * parent) : QGameItem(parent) // Block constructor
{
    // dummy
    position = -1;
    block_type = BlockType::NONE;
}


Block::~Block()                                     // Block Destructor
{
}

// public method 

BlockType::Type Block::getType() const              // get block_type              
{
    return block_type;
}


void Block::setPosition(int position)               //set block_position
{
    this->position = position;
}

int Block::getPosition(){                           //get block_position
    return position;
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event){   // block_clicked event
    qDebug() << "block:" << position;
    emit blockClicked(this);
}
