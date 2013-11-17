#pragma once
#include "block.h"

// circular dependency
class Board;
class Player;

class Block
{
public:
    enum CornerType
    {
        DORMITORY,
        CALLTAXI,
        BREAKSEMESTER,
        PLURALMAJOR
    };
	int blocknumber;//blocknumber 혹은 board의 어레이 번호로 각 블럭 번호를 관리할 수 있으면 좋겠다.. 아니면 이걸 원표가 하고있나!?
                    //0번 =dormitory~

public:

    Block();
    virtual ~Block();
    virtual void enter(Player* player);
};

