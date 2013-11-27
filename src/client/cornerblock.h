#pragma once
#include "player.h"
#include "block.h"
#include <ctime>
#include <cstdlib>


class CornerBlock : public Block
{
public:
    enum CornerType {
        DORMITORY, THE61CALL, BREAKSEMESTER, PLURALMAJOR
    };

private:
    CornerType block_type;
public:
    CornerBlock();
    virtual ~CornerBlock();

    virtual void enter(Player* player);
    void inCornerBlock(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inDormitory(Player* player);
    void in61Call(Player* player);
    void inBreakSemester(Player* player);
    void inPluralMajor(Player* player);
};
