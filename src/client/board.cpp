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
<<<<<<< HEAD
    blocks = new Block*[36];


    blocks[0] = new CornerBlock(1);

    blocks[1] = new SubjectBlock;
    blocks[2] = new SubjectBlock;
    blocks[3] = new SubjectBlock;

    blocks[4] = new EventBlock; 
    
    blocks[5] = new SubjectBlock;
    blocks[6] = new SubjectBlock;
    blocks[7] = new SubjectBlock;
    
    blocks[8] = new CornerBlock;
    
    blocks[9] = new SubjectBlock;
    blocks[10] = new SubjectBlock;
    blocks[11] = new SubjectBlock;
    
    blocks[12] = new EventBlock;
    
    blocks[13] = new SubjectBlock;
    blocks[14] = new SubjectBlock;
    blocks[15] = new SubjectBlock;
    
    blocks[16] = new CornerBlock;
    
    blocks[17] = new SubjectBlock;
    blocks[18] = new SubjectBlock;
    blocks[19] = new SubjectBlock;
    
    blocks[20] = new EventBlock;
    
    blocks[21] = new SubjectBlock;
    blocks[22] = new SubjectBlock;
    blocks[23] = new SubjectBlock;
    
    blocks[24] = new CornerBlock;
    
    blocks[25] = new SubjectBlock;
    blocks[26] = new SubjectBlock;
    blocks[27] = new SubjectBlock;
    
    blocks[28] = new EventBlock;
    
    blocks[29] = new SubjectBlock;
    blocks[30] = new SubjectBlock;
    blocks[31] = new SubjectBlock;
    
    for(int i=0; i<36; i++) {
=======
    using namespace SubjectType;

    blocks = new Block*[32];

    blocks[0] = new CornerBlock(CornerType::DORM); // dorm

    blocks[1] = new SubjectBlock(CSE,"CSE1",45); // cse 전산 45
    blocks[2] = new SubjectBlock(CSE,"CSE2",85); // cse 객체 85
    blocks[3] = new SubjectBlock(CSE,"CSE3",125); // cse OS 125

    blocks[4] = new FireFridayBlock(FireFridayType::TONGZIP); //통집

    blocks[5] = new SubjectBlock(ME,"ME1",50); // me 기공개론 50
    blocks[6] = new SubjectBlock(ME,"ME2",90); //me 열역학 90
    blocks[7] = new SubjectBlock(ME,"ME3",130); //me 시스템설계 130

    blocks[8] = new CornerBlock(CornerType::BREAKSEM); // 휴학
    
    blocks[9] = new SubjectBlock(MATH,"MATH1",55); //math 응선대 55
    blocks[10] = new SubjectBlock(MATH,"MATH2",95); //math 해석학 95
    blocks[11] = new SubjectBlock(MATH,"MATH3",135); //math 위상수학 135

    blocks[12] = new EventBlock; //Event

    blocks[13] = new SubjectBlock(EE,"EE1",60); //ee 반도체 60
    blocks[14] = new SubjectBlock(EE,"EE2",100); //ee 신호및시스템 100
    blocks[15] = new SubjectBlock(EE,"EE3",140); //ee 전자회로 140

    blocks[16] = new CornerBlock(CornerType::PLURAL); //복수전공
    
    blocks[17] = new SubjectBlock(PHYS,"PHYS1",65); //phys 일반물리 65
    blocks[18] = new SubjectBlock(PHYS,"PHYS2",105); //phys 현대물리 105
    blocks[19] = new SubjectBlock(PHYS,"PHYS3",145); //phys 양자물리 145

    blocks[20] = new FireFridayBlock(FireFridayType::SEOULJONGBIN); // 설종빈

    blocks[21] = new SubjectBlock(BIO,"BIO1",70); //bio 일반생명 70
    blocks[22] = new SubjectBlock(BIO,"BIO2",110); //bio 분자생물학 110
    blocks[23] = new SubjectBlock(BIO,"BIO3",150); //bio 유전학 150

    blocks[24] = new CornerBlock(CornerType::CALLTAXI); //61콜

    blocks[25] = new SubjectBlock(CHEM,"CHEM1",75); //chem 일반화학 75
    blocks[26] = new SubjectBlock(CHEM,"CHEM1",115); //chem 유기화학 115
    blocks[27] = new SubjectBlock(CHEM,"CHEM1",155); //chem 물리화학 155
    
    blocks[28] = new EventBlock; // Event

    blocks[29] = new SubjectBlock(MSE,"MSE1",80); //mse 산경입문 80
    blocks[30] = new SubjectBlock(MSE,"MSE1",120); //mse 제품생산공정 120
    blocks[31] = new SubjectBlock(MSE,"MSE1",160); //mse 품질공학 160
    
    for(int i=0; i<32; i++)
    {
>>>>>>> fcb0d30314a1c4ee5120a289d960a0cf6b07b0f0
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

