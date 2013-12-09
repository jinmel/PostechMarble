#include "dice.h"
#include <qDebug>
#include <ctime>
#include <cstdlib>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QTimeLine>

using namespace std;

Dice::Dice()    //dice constructor
{
    qDebug() << "Dice Created";
    srand((unsigned)time(NULL));
    value1 = 0;
    value2 = 0;
    roll_sound = new QMediaPlayer();            // dice roll sounde setting
    roll_sound->setVolume(100);
    effect_sound = new QMediaPlayer();
    effect_sound->setVolume(100);
    timeline = new QTimeLine(1300);

    //(5,4)플레이어 1응선대 이수
    dicevaluequeue1.enqueue(5);
    dicevaluequeue2.enqueue(5);

    //(5,4)플레이어 2 응선대 벌금
    dicevaluequeue1.enqueue(2);
    dicevaluequeue2.enqueue(4);

    dicevaluequeue1.enqueue(4);
    dicevaluequeue2.enqueue(6);

    //(1,1)플레이어 3 객체 더블
    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(1);


    //(2,4)플레이어 3 더블 휴학
    dicevaluequeue1.enqueue(2);
    dicevaluequeue2.enqueue(4);

    //(1,2)플레이어 1 이벤트 블록가서 설종빈 ㄱㄱ
    dicevaluequeue1.enqueue(2);
    dicevaluequeue2.enqueue(4);
    //(2,2) 플레이어 2 복수전공 당첨
    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(1);

    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(4);


    //(3,5) 플레이어 2 육일콜 도착해서 해석학
    dicevaluequeue1.enqueue(6);
    dicevaluequeue2.enqueue(6);

    dicevaluequeue1.enqueue(5);
    dicevaluequeue2.enqueue(3);

    dicevaluequeue1.enqueue(4);
    dicevaluequeue2.enqueue(6);

    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(2);

    dicevaluequeue1.enqueue(5);
    dicevaluequeue2.enqueue(3);

    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(2);

    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(3);

    dicevaluequeue1.enqueue(1);
    dicevaluequeue2.enqueue(2);

    dicevaluequeue1.enqueue(2);
    dicevaluequeue2.enqueue(3);

    dicevaluequeue1.enqueue(3);
    dicevaluequeue2.enqueue(1);


    connect(timeline, SIGNAL(finished()), this, SLOT(afterRollSound()));
}

Dice::~Dice()   // dice destructor
{
    qDebug() << "Dice Destroyed";
    delete roll_sound;
    delete effect_sound;
    delete timeline;
}


// Initialize Static Members
Dice* Dice::m_inst = NULL;

Dice* Dice::getInst()
{
    // create new instance if null
    if (!m_inst) {
        m_inst = new Dice();
    }

    return m_inst;
}

void Dice::delInst()
{
    // delete an instance
    if (m_inst) {
        delete m_inst;
        m_inst = NULL;
    }

    return;
}


// Methods
void Dice::roll()           // dice roll 
{
    qDebug() << "Dice Rolled";

    value1 = rand() % 6 + 1;        // there are two dices
    value2 = rand() % 6 + 1;

    value1 = dicevaluequeue1.dequeue();
    value2 = dicevaluequeue2.dequeue();

    emit diceRolled(getValue(),isDouble());
    emit firstDiceRolled(value1);
    emit secondDiceRolled(value2);
    emit diceRolled(getValue());
    emit diceRolled(this);

    timeline->start();

    // play sound
    roll_sound->setMedia(QUrl::fromLocalFile(QFileInfo("sound/roll.mp3").absoluteFilePath()));
    roll_sound->play();
}

bool Dice::isDouble() // both values of dices are same => true , else false
{
    return (value1 == value2);
}

int Dice::getValue()    // sum of two value
{
    return value1 + value2;
}
int Dice::getFirstDice()    // 1st dice value
{
    return value1;
}

int Dice::getSecondDice()       //2nd dice value
{
    return value2;
}

void Dice::afterRollSound()         // different sounds up to sum of the values
{
    QString path = "";

    if(isDouble()) {
        path += "sound/double.wav";

        // emit singal for double popup
        emit diceDouble();
    }
    else {
        switch(value1 + value2) {
            case 2:
                path += "sound/two.wav";
                break;
            case 3:
                path += "sound/three.wav";
                break;
            case 4:
                path += "sound/four.wav";
                break;
            case 5:
                path += "sound/five.wav";
                break;
            case 6:
                path += "sound/six.wav";
                break;
            case 7:
                path += "sound/seven.wav";
                break;
            case 8:
                path += "sound/eight.wav";
                break;
            case 9:
                path += "sound/nine.wav";
                break;
            case 10:
                path += "sound/ten.wav";
                break;
            case 11:
                path += "sound/eleven.wav";
                break;
            case 12:
                path += "sound/twelve.wav";
                break;
        }
    }
        
    effect_sound->setMedia(QUrl::fromLocalFile(QFileInfo(path).absoluteFilePath()));
    effect_sound->play();

}
