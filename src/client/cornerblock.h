#ifndef CORNERBLOCK_H
#define CORNERBLOCK_H

enum CornerType {DORMITORY, THE61CALL, BREAKSEMESTER, PLURALMAJOR};
using namespace std;

class CornerBlock : public Block
{
private:
    CornerType theBlockType;


public:
    CornerBlock();
    void inCornerBlock(Player* player);//in Cornerblock, execute this function
						//This function : type check and call correct function
	void inDormitory(Player* player);
    void in61Call(Player* player);
    void inBreakSemester(Player* player);
    void inPluralMajor(Player* player);
};

#endif // CORNERBLOCK_H
