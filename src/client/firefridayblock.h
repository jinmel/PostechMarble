#pragma once
#include "block.h"
#include "types.h"
#include <QMediaPlayer>

class FireFridayBlock : public Block
{
private:
    FireFridayType::Type firefriday_type;
    QMediaPlayer *sound;

public:
    FireFridayBlock(QGameItem * parent,FireFridayType::Type type);
    virtual ~FireFridayBlock();
    virtual void enter(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inSEOULJONGBIN(Player* player);
    void inTONGZIP(Player* player);
};
