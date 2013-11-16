#pragma once

using namespace std;

class CornerBlock : public Block
{
public:
    enum CornerType {
        DORMITORY, THE61CALL, BREAKSEMESTER, PLURALMAJOR
    };

private:
    CornerType theBlockType;

public:
    CornerBlock();
    ~CornerBlock();
    void inCornerBlock(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inDormitory(Player* player);
    void in61Call(Player* player);
    void inBreakSemester(Player* player);
    void inPluralMajor(Player* player);
};
