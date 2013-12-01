#include <iostream>
#include "board.h"
#include "eventblock.h"
#include "subjectblock.h"
#include "cornerblock.h"
#include "firefridayblock.h"
#include <QTransform>


using namespace std;


// Constructor & Destructor
Board::Board(QGraphicsScene * scene,MainWindow * window) : QGameItem(scene,window)
{
    using namespace SubjectType;
    //set background
    setImage(":/images/ingame/board/back_white.png");
    blocks = new Block*[32];

    QTransform trans;
    trans.rotate(90);

    /*
     * Corner block size : 142 x 114
     * Horizontal block size : 91 x 114
     * Vertical block size : 142 x 64
     * Board size : 1012 x 740
     */

    const int corner_w = 142;
    const int corner_h = 114;
    const int hblock_w = 91;
    const int hblock_h = 114;
    const int vblock_w = 142;
    const int vblock_h = 64;


    //TODO : set position and images... -ㅁ-;;
    blocks[0] = new CornerBlock(this,CornerType::DORM); // dorm
    blocks[1] = new SubjectBlock(this,CSE,"CSE1",45); // cse 전산 45
    blocks[2] = new SubjectBlock(this,CSE,"CSE2",85); // cse 객체 85
    blocks[3] = new SubjectBlock(this,CSE,"CSE3",125); // cse OS 125
    blocks[4] = new FireFridayBlock(this,FireFridayType::TONGZIP); //통집

    blocks[5] = new SubjectBlock(this,ME,"ME1",50); // me 기공개론 50
    blocks[6] = new SubjectBlock(this,ME,"ME2",90); //me 열역학 90
    blocks[7] = new SubjectBlock(this,ME,"ME3",130); //me 시스템설계 130


    //corner block
    blocks[8] = new CornerBlock(this,CornerType::BREAKSEM); // 휴학
    blocks[8]->setImage(":/images/ingame/block/corner.png");

    //MATH subject block
    blocks[9] = new SubjectBlock(this,MATH,"MATH1",55); //math 응선대 55
    blocks[9]->setImage(":/images/ingame/block/MATH_background.png");
    blocks[9]->setPos(corner_w,0);
    blocks[10] = new SubjectBlock(this,MATH,"MATH2",95); //math 해석학 95
    blocks[10]->setImage(":/images/ingame/block/MATH_background.png");
    blocks[10]->setPos(corner_w + hblock_w * 1,0);
    blocks[11] = new SubjectBlock(this,MATH,"MATH3",135); //math 위상수학 135
    blocks[11]->setImage(":/images/ingame/block/MATH_background.png");
    blocks[11]->setPos(corner_w + hblock_w * 2,0);

    //Event block
    blocks[12] = new EventBlock(this); //Event
    blocks[12]->setImage(":/images/ingame/block/ME_background.png");
    blocks[12]->setPos(corner_w + hblock_w * 3,0);

    //EE subject block
    blocks[13] = new SubjectBlock(this,EE,"EE1",60); //ee 반도체 60
    blocks[13]->setImage(":/images/ingame/block/EE_background.png");
    blocks[13]->setPos(corner_w + hblock_w * 4,0);
    blocks[14] = new SubjectBlock(this,EE,"EE2",100); //ee 신호및시스템 100
    blocks[14]->setImage(":/images/ingame/block/EE_background.png");
    blocks[14]->setPos(corner_w + hblock_w * 5,0);
    blocks[15] = new SubjectBlock(this,EE,"EE3",140); //ee 전자회로 140
    blocks[15]->setImage(":/images/ingame/block/EE_background.png");
    blocks[15]->setPos(corner_w + hblock_w * 6,0);

    //Event Block
    blocks[16] = new CornerBlock(this,CornerType::PLURAL); //복수전공

    
    blocks[17] = new SubjectBlock(this,PHYS,"PHYS1",65); //phys 일반물리 65
    blocks[18] = new SubjectBlock(this,PHYS,"PHYS2",105); //phys 현대물리 105
    blocks[19] = new SubjectBlock(this,PHYS,"PHYS3",145); //phys 양자물리 145

    blocks[20] = new FireFridayBlock(this,FireFridayType::SEOULJONGBIN); // 설종빈

    blocks[21] = new SubjectBlock(this,BIO,"BIO1",70); //bio 일반생명 70
    blocks[22] = new SubjectBlock(this,BIO,"BIO2",110); //bio 분자생물학 110
    blocks[23] = new SubjectBlock(this,BIO,"BIO3",150); //bio 유전학 150

    blocks[24] = new CornerBlock(this,CornerType::CALLTAXI); //61콜

    blocks[25] = new SubjectBlock(this,CHEM,"CHEM1",75); //chem 일반화학 75
    blocks[26] = new SubjectBlock(this,CHEM,"CHEM1",115); //chem 유기화학 115
    blocks[27] = new SubjectBlock(this,CHEM,"CHEM1",155); //chem 물리화학 155
    
    blocks[28] = new EventBlock(this); // Event

    blocks[29] = new SubjectBlock(this,MSE,"MSE1",80); //mse 산경입문 80
    blocks[30] = new SubjectBlock(this,MSE,"MSE1",120); //mse 제품생산공정 120
    blocks[31] = new SubjectBlock(this,MSE,"MSE1",160); //mse 품질공학 160
    
    for(int i=0; i<32; i++)
    {
        blocks[i]->setPosition(i);
    }

}


Board::~Board()
{
    for(int i=0; i<32; i++)
        delete blocks[i];
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

