#include "ingamescene.h"
#include <QPixmap>
#include <QtGlobal>
#include "dice.h"

IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent)
{
    MainWindow * w = dynamic_cast<MainWindow*>(parent);
    Q_CHECK_PTR(w);
    dice_graphic = new DiceGraphicItem(this,w);
    dice_graphic->setPos(800,800);

    first_panel = new DiceValuePanel(this,w);
    first_panel->setPos(500,500);
    second_panel = new DiceValuePanel(this,w);
    second_panel->setPos(300,300);
    connect(dice_graphic,SIGNAL(firstValueChanged(int)),first_panel,SLOT(setValue(int)));
    connect(dice_graphic,SIGNAL(secondValueChanged(int)),second_panel,SLOT(setValue(int)));
}

IngameScene::~IngameScene(){
    delete first_panel;
    delete second_panel;
    delete dice_graphic;
    delete background;
}

QGraphicsPixmapItem* IngameScene::setBackgroundPixmap(const char * filename){
    return this->addPixmap(QPixmap(filename));
}

QGraphicsPixmapItem* IngameScene::backgroundPixmap(){
    return background;
}

DiceGraphicItem::DiceGraphicItem(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene,window){
    this->setImage(":/images/ingame/button.png");
}

void DiceGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->setImage(":/images/ingame/button_pushed.png");
    QGameItem::mousePressEvent(event);
}

void DiceGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    this->setImage(":/images/ingame/button.png");
    Dice * dice = Dice::getInst();
    dice->roll();
    int value1 = dice->getFirstDice();
    int value2 = dice->getSecondDice();

    //emit two signals to dice panels
    emit firstValueChanged(value1);
    emit secondValueChanged(value2);
    QGameItem::mouseReleaseEvent(event);
}

DiceValuePanel::DiceValuePanel(QGraphicsScene *scene, MainWindow *window) : QGameItem(scene,window)
{
    this->setImage(":/images/ingame/dice/dice3.png");
    diceValue = 3; //default value
}

void DiceValuePanel::setValue(int value)
{
    switch(value){
    case 1:
        this->setImage(":/images/ingame/dice/dice1.png");
        break;
    case 2:
        this->setImage(":/images/ingame/dice/dice2.png");
        break;
    case 3:
        this->setImage(":/images/ingame/dice/dice3.png");
        break;
    case 4:
        this->setImage(":/images/ingame/dice/dice4.png");
        break;
    case 5:
        this->setImage(":/images/ingame/dice/dice5.png");
        break;
    case 6:
        this->setImage(":/images/ingame/dice/dice6.png");
        break;
    }
}


