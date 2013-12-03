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
    using namespace BlockCoords;
    //set background
    setImage(":/images/ingame/board/back_white.png");
    blocks = new Block*[32];

    QTransform flip;
    flip.rotate(180);

    /*
     * Corner block size : 142 x 114
     * Horizontal block size : 91 x 114
     * Vertical block size : 142 x 64
     * Board size : 921 x 676
     */

    //TODO : set position and images... -ㅁ-;;

    //corner block
    blocks[0] = new CornerBlock(this,CornerType::DORM); // dorm
    blocks[0]->setImage(":/images/ingame/block/corner.png");
    blocks[0]->setPos(block_coord[0]);
    //CSED subject block
    blocks[1] = new SubjectBlock(this,CSED,"CSED1",45); // cse 전산 45
    blocks[1]->setImage(":/images/ingame/block/vertical/CSED_background_vertical.png");
    blocks[1]->setPos(block_coord[1]);
    blocks[2] = new SubjectBlock(this,CSED,"CSED2",85); // cse 객체 85
    blocks[2]->setImage(":/images/ingame/block/vertical/CSED_background_vertical.png");
    blocks[2]->setPos(block_coord[2]);
    blocks[3] = new SubjectBlock(this,CSED,"CSED3",125); // cse OS 125
    blocks[3]->setImage(":/images/ingame/block/vertical/CSED_background_vertical.png");
    blocks[3]->setPos(block_coord[3]);

    //Event block
    blocks[4] = new FireFridayBlock(this,FireFridayType::TONGZIP); //통집
    blocks[4]->setImage(":/images/ingame/block/vertical/Event_block_vertical.png");
    blocks[4]->setPos(block_coord[4]);

    //ME subject block
    blocks[5] = new SubjectBlock(this,ME,"ME1",50); // me 기공개론 50
    blocks[5]->setImage(":/images/ingame/block/vertical/ME_background_vertical.png");
    blocks[5]->setPos(block_coord[5]);
    blocks[6] = new SubjectBlock(this,ME,"ME2",90); //me 열역학 90
    blocks[6]->setImage(":/images/ingame/block/vertical/ME_background_vertical.png");
    blocks[6]->setPos(block_coord[6]);
    blocks[7] = new SubjectBlock(this,ME,"ME3",130); //me 시스템설계 130
    blocks[7]->setImage(":/images/ingame/block/vertical/ME_background_vertical.png");
    blocks[7]->setPos(block_coord[7]);

    //corner block
    blocks[8] = new CornerBlock(this,CornerType::BREAKSEM); // 휴학
    blocks[8]->setImage(":/images/ingame/block/corner.png");
    blocks[8]->setPos(block_coord[8]);


    //MATH subject block
    blocks[9] = new SubjectBlock(this,MATH,"MATH1",55); //math 응선대 55
    blocks[9]->setImage(":/images/ingame/block/MATH_background.png");
    blocks[9]->setPos(block_coord[9]);
    blocks[10] = new SubjectBlock(this,MATH,"MATH2",95); //math 해석학 95
    blocks[10]->setImage(":/images/ingame/block/MATH_background.png");
    blocks[10]->setPos(block_coord[10]);
    blocks[11] = new SubjectBlock(this,MATH,"MATH3",135); //math 위상수학 135
    blocks[11]->setImage(":/images/ingame/block/MATH_background.png");
    blocks[11]->setPos(block_coord[11]);

    //Event block
    blocks[12] = new EventBlock(this); //Event
    blocks[12]->setImage(":/images/ingame/block/Event_block.png");
    blocks[12]->setPos(block_coord[12]);


    //EE subject block
    blocks[13] = new SubjectBlock(this,EE,"EE1",60); //ee 반도체 60
    blocks[13]->setImage(":/images/ingame/block/EE_background.png");
    blocks[13]->setPos(block_coord[13]);
    blocks[14] = new SubjectBlock(this,EE,"EE2",100); //ee 신호및시스템 100
    blocks[14]->setImage(":/images/ingame/block/EE_background.png");
    blocks[14]->setPos(block_coord[14]);
    blocks[15] = new SubjectBlock(this,EE,"EE3",140); //ee 전자회로 140
    blocks[15]->setImage(":/images/ingame/block/EE_background.png");
    blocks[15]->setPos(block_coord[15]);

    //Corner block
    blocks[16] = new CornerBlock(this,CornerType::PLURAL); //복수전공
    blocks[16]->setImage(":/images/ingame/block/corner.png");
    blocks[16]->setPos(block_coord[16]);

    //PHYS subject block
    blocks[17] = new SubjectBlock(this,PHYS,"PHYS1",65); //phys 일반물리 65
    blocks[17]->setImage(":/images/ingame/block/vertical/PHYS_background_vertical.png");
    blocks[17]->setPos(block_coord[17]);
    blocks[17]->rotateImage(180);
    blocks[18] = new SubjectBlock(this,PHYS,"PHYS2",105); //phys 현대물리 105
    blocks[18]->setImage(":/images/ingame/block/vertical/PHYS_background_vertical.png");
    blocks[18]->setPos(block_coord[18]);
    blocks[18]->rotateImage(180);
    blocks[19] = new SubjectBlock(this,PHYS,"PHYS3",145); //phys 양자물리 145
    blocks[19]->setImage(":/images/ingame/block/vertical/PHYS_background_vertical.png");
    blocks[19]->setPos(block_coord[19]);
    blocks[19]->rotateImage(180);

    //Event block
    blocks[20] = new FireFridayBlock(this,FireFridayType::SEOULJONGBIN); // 설종빈
    blocks[20]->setImage(":/images/ingame/block/vertical/Event_block_vertical.png");
    blocks[20]->setPos(block_coord[20]);

    //BIO subject block
    blocks[21] = new SubjectBlock(this,BIO,"BIO1",70); //bio 일반생명 70
    blocks[21]->setImage(":/images/ingame/block/vertical/BIO_background_vertical.png");
    blocks[21]->setPos(block_coord[21]);
    blocks[21]->rotateImage(180);
    blocks[22] = new SubjectBlock(this,BIO,"BIO2",110); //bio 분자생물학 110
    blocks[22]->setImage(":/images/ingame/block/vertical/BIO_background_vertical.png");
    blocks[22]->setPos(block_coord[22]);
    blocks[22]->rotateImage(180);
    blocks[23] = new SubjectBlock(this,BIO,"BIO3",150); //bio 유전학 150
    blocks[23]->setImage(":/images/ingame/block/vertical/BIO_background_vertical.png");
    blocks[23]->setPos(block_coord[23]);
    blocks[23]->rotateImage(180);
    //Corner block
    blocks[24] = new CornerBlock(this,CornerType::CALLTAXI); //61콜
    blocks[24]->setImage(":/images/ingame/block/corner.png");
    blocks[24]->setPos(block_coord[24]);

    //CHEM block
    blocks[25] = new SubjectBlock(this,CHEM,"CHEM1",75); //chem 일반화학 75
    blocks[25]->setImage(":/images/ingame/block/CHEM_background.png");
    blocks[25]->setPos(block_coord[25]);
    blocks[25]->rotateImage(180);
    blocks[26] = new SubjectBlock(this,CHEM,"CHEM2",115); //chem 유기화학 115
    blocks[26]->setImage(":/images/ingame/block/CHEM_background.png");
    blocks[26]->setPos(block_coord[26]);
    blocks[26]->rotateImage(180);
    blocks[27] = new SubjectBlock(this,CHEM,"CHEM3",155); //chem 물리화학 155
    blocks[27]->setImage(":/images/ingame/block/CHEM_background.png");
    blocks[27]->setPos(block_coord[27]);
    blocks[27]->rotateImage(180);
    
    //Event block
    blocks[28] = new EventBlock(this); // Event
    blocks[28]->setImage(":/images/ingame/block/Event_block.png");
    blocks[28]->setPos(block_coord[28]);

    //IME block
    blocks[29] = new SubjectBlock(this,IME,"IME1",80); //mse 산경입문 80
    blocks[29]->setImage(":/images/ingame/block/IME_background.png");
    blocks[29]->setPos(block_coord[29]);
    blocks[29]->rotateImage(180);
    blocks[30] = new SubjectBlock(this,IME,"IME2",120); //mse 제품생산공정 120
    blocks[30]->setImage(":/images/ingame/block/IME_background.png");
    blocks[30]->setPos(block_coord[30]);
    blocks[30]->rotateImage(180);
    blocks[31] = new SubjectBlock(this,IME,"IME3",160); //mse 품질공학 160
    blocks[31]->setImage(":/images/ingame/block/IME_background.png");
    blocks[31]->setPos(block_coord[31]);
    blocks[31]->rotateImage(180);

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

namespace BlockCoords {
    const int corner_w = 142;
    const int corner_h = 114;
    const int hblock_w = 91;
//const int hblock_h = 114; //not used
//const int vblock_w = 142; //not used
    const int vblock_h = 64;

    QPointF block_coord[32] = {
    QPointF(0,corner_h + vblock_h * 7),
    QPointF(0,corner_h + vblock_h * 6),
    QPointF(0,corner_h + vblock_h * 5),
    QPointF(0,corner_h + vblock_h * 4),
    QPointF(0,corner_h + vblock_h * 3),
    QPointF(0,corner_h + vblock_h * 2),
    QPointF(0,corner_h + vblock_h * 1),
    QPointF(0,corner_h + vblock_h * 0),
    QPointF(0,0),
    QPointF(corner_w + hblock_w * 0,0),
    QPointF(corner_w + hblock_w * 1,0),
    QPointF(corner_w + hblock_w * 2,0),
    QPointF(corner_w + hblock_w * 3,0),
    QPointF(corner_w + hblock_w * 4,0),
    QPointF(corner_w + hblock_w * 5,0),
    QPointF(corner_w + hblock_w * 6,0),
    QPointF(corner_w + hblock_w * 7,0),
    QPointF(corner_w + hblock_w * 7, corner_h),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 1),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 2),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 3),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 4),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 5),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 6),
    QPointF(corner_w + hblock_w * 7, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 6, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 5, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 4, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 3, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 2, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 1, corner_h + vblock_h * 7),
    QPointF(corner_w + hblock_w * 0, corner_h + vblock_h * 7)
    };

    QPointF corner_coord[4] = {
        block_coord[0],
        block_coord[8],
        block_coord[16],
        block_coord[24],
    };
}
