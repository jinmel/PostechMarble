#include "block.h"

// Constructor & Destructor
Block::Block()
{
    // dummy
    position = -1;
}


Block::~Block()
{
}


// Methods
BlockType::Type Block::getType() const
{
    return block_type;
}


void Block::setPosition(int position)
{
    this->position = position;
}
