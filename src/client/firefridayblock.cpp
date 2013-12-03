#include <iostream>
#include "block.h"
#include "firefridayblock.h"
#include "player.h"
#include "dice.h"
#include "sellpopup.h"
// Constructor & Destructor
FireFridayBlock::FireFridayBlock(QGameItem * parent,FireFridayType::Type type)
    : Block(parent)
{
    block_type = type;
}

FireFridayBlock::~FireFridayBlock()
{

}


// Methods
void FireFridayBlock::enter(Player *player)
{
    using namespace FireFridayType;

    switch(block_type)
   {    
        case SEOULJONGBIN: inSEOULJONGBIN(player);
            break;
        case TONGZIP: inTONGZIP(player);
            break;
    }

}

void FireFridayBlock::inSEOULJONGBIN(Player *player)
{
    if(player->getType()!=CharacterType::ALCOHOLIC)
    {
        if(player->getEnergy()>=100)
        player->setEnergy(player->getEnergy() - 100);
        else
        {
                Sellpopup * popup = Sellpopup();
                popup->show();
                player->setEnergy(player->getEnergy()-100);
        }
    }
}

void FireFridayBlock::inTONGZIP(Player *player)
{
    if(player->getType()!=CharacterType::ALCOHOLIC)
    player->setEnergy(player->getEnergy() - 100);
}
