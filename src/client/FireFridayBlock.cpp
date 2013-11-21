#include <iostream>
#include "block.h"
#include "FireFridayBlock.h"
#include "player.h"
#include "dice.h"


FireFridayBlock::FireFridayBlock()
{

}

FireFridayBlock::~FireFridayBlock()
{

}

void FireFridayBlock::inFireFridayBlock(Player *player)
{
    switch(player->getPosition())
   {    case 5: inTWODARI(player);
            break;
        case 17: inSEOULJONGBIN(player);
            break;
        case 26: inTONGZIP(player);
            break;
        case 28: inCHAMPYO(player);
            break;
    }

}


void FireFridayBlock::inSEOULJONGBIN(Player *player)
{

}

void FireFridayBlock::inCHAMPYO(Player *player)
{

}

void FireFridayBlock::inTONGZIP(Player *player)
{

}

void FireFridayBlock::inTWODARI(Player *player)
{

}

