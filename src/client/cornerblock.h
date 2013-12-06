#pragma once
#include <QMediaPlayer>
#include "player.h"
#include "block.h"
#include "types.h"
#include "qgameitem.h"

class CornerBlock : public Block
{
private:
    CornerType::Type corner_type;
    QMediaPlayer *effect_player;

public:
    CornerBlock(QGameItem * parent,CornerType::Type type);
    virtual ~CornerBlock();

    virtual void enter(Player* player);
    void inDormitory(Player* player);
    void in61Call(Player* player);
    void inBreakSemester(Player* player);
    void inPluralMajor(Player* player);
};
