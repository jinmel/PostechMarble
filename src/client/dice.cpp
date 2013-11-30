#include "dice.h"
#include <qDebug>
#include <ctime>
#include <cstdlib>

using namespace std;

Dice::Dice()
{
    qDebug() << "Dice Created";

    srand((unsigned)time(NULL));
    value1 = 0;
    value2 = 0;
}

Dice::~Dice()
{
    qDebug() << "Dice Destroyed";
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
    value1 = rand() % 6 + 1;
    value2 = rand() % 6 + 1;
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
