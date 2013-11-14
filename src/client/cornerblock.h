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
    void inCornerBlock();//cornerblock에 들어와서 이 함수를 실행하면 함수 내에서 칸의 타입을 체크하고 그에 맞는 함수를 call한다.
    void inDormitory();
    void in61Call();
    void inBreakSemester();
    void inPluralMajor();
};

#endif // CORNERBLOCK_H
