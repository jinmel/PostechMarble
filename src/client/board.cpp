#include <iostream>
#include "board.h"
#include "eventblock.h"
#include "subjectblock.h"
#include "cornerblock.h"
#include "firefridayblock.h"

using namespace std;

// Constructor & Destructor
Board::Board()
{
    blocks = new Block*[32];


    blocks[0] = new CornerBlock; // dorm

    blocks[1] = new SubjectBlock; // cse 전산 45
    blocks[2] = new SubjectBlock; // cse 객체 85
    blocks[3] = new SubjectBlock; // cse OS 125


    blocks[4] = new SubjectBlock; // me 기공개론 50

    blocks[5] = new FireFridayBlock; //투다리
    blocks[6] = new SubjectBlock; //me 열역학 90
    blocks[7] = new SubjectBlock; //me 시스템설계 130

    blocks[8] = new CornerBlock; // 휴학
    
    blocks[9] = new SubjectBlock; //math 응선대 55

    blocks[10] = new SubjectBlock; //math 해석학 95
    blocks[11] = new SubjectBlock; //math 위상수학 135 
    blocks[12] = new EventBlock; 

    blocks[13] = new SubjectBlock; //ee 반도체 60
    
    blocks[14] = new SubjectBlock; //ee 신호및시스템 100
    blocks[15] = new SubjectBlock; //ee 전자회로 140
    blocks[16] = new CornerBlock; //복수전공
    
    blocks[17] = new SubjectBlock; //phys 일반물리 65

    blocks[18] = new SubjectBlock; //phys 현대물리 105
    
    blocks[19] = new SubjectBlock; //phys 양자물리 145
    blocks[20] = new SubjectBlock; //bio 일반생명 70
    blocks[21] = new SubjectBlock; //bio 분자생물학 110

    blocks[22] = new SubjectBlock; //bio 유전학 150

    blocks[23] = new FireFridayBlock; //통집
    blocks[24] = new CornerBlock; //61콜
    blocks[25] = new SubjectBlock; //chem 일반화학 75
    
    blocks[26] = new SubjectBlock; //chem 유기화학 115

    blocks[27] = new SubjectBlock; //chem 물리화학 155
    
    blocks[28] = new EventBlock; //

    blocks[29] = new SubjectBlock; //mse 산경입문 80
    blocks[30] = new SubjectBlock; //mse 제품생산공정 120
    blocks[31] = new SubjectBlock; //mse 품질공학 160
    
    for(int i=0; i<32; i++) {
        blocks[i]->setPosition(i);
    }

    cout << "Board Created" << endl;
}


Board::~Board()
{
    delete[] blocks;
}


// Methods
int Board::getLength() const
{
    return length;
}


Block* Board::getBlock(int position) const
{
    return blocks[position];
}


void Board::enter(Player* player)
{
    blocks[player->getPosition()]->enter(player);
}

