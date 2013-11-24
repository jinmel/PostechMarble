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
void Block::setPosition(int position)
{
    this->position = position;
}
