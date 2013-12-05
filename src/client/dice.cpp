#include "dice.h"
#include <qDebug>
#include <ctime>
#include <cstdlib>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QTimeLine>

using namespace std;

Dice::Dice()
{
    qDebug() << "Dice Created";
    srand((unsigned)time(NULL));
    value1 = 0;
    value2 = 0;
    roll_sound = new QMediaPlayer();
    roll_sound->setVolume(100);
    effect_sound = new QMediaPlayer();
    effect_sound->setVolume(100);
    timeline = new QTimeLine(1300);

    connect(timeline, SIGNAL(finished()), this, SLOT(afterRollSound()));
}

Dice::~Dice()
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
void Dice::roll()
{
    qDebug() << "Dice Rolled";

    value1 = rand() % 6 + 1;
    value2 = rand() % 6 + 1;

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

bool Dice::isDouble()
{
    return (value1 == value2);
}

int Dice::getValue()
{
    return value1 + value2;
}
int Dice::getFirstDice()
{
    return value1;
}

int Dice::getSecondDice()
{
    return value2;
}

void Dice::afterRollSound()
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
