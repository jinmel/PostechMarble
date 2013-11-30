#include "ingamescene.h"
#include <QPixmap>
#include <QtGlobal>
#include "dice.h"

IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent), window(dynamic_cast<MainWindow*>(parent))
{

    Q_CHECK_PTR(window);

    setBackgroundPixmap(":/images/ingame/background_test.jpg");
    //주사위 그래픽
    dice_graphic = new DiceGraphicItem(this,window);
    dice_graphic->setPos(900,400);

    //주사위 패널 첫번째
    first_dice_panel = new DiceValuePanel(this,window);
    first_dice_panel->setPos(400,400);
    //주사위 패널 두번째
    second_dice_panel = new DiceValuePanel(this,window);
    second_dice_panel->setPos(500,400);

    //Signal / Slots connection
    Dice * dice = Dice::getInst();
    connect(dice,SIGNAL(firstDiceRolled(int)),first_dice_panel,SLOT(setValue(int)));
    connect(dice,SIGNAL(secondDiceRolled(int)),second_dice_panel,SLOT(setValue(int)));
}

IngameScene::~IngameScene(){
    delete first_dice_panel;
    delete second_dice_panel;
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
    //버튼 초기상태 이미지
    this->setImage(":/images/ingame/button.png");
}

void DiceGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //버튼이 눌렸을 때의 이미지로 바꿈
    this->setImage(":/images/ingame/button_pushed.png");
}

void DiceGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //마우스에서 땠을 경우 다시 초기상태 이미지로 바꿈
    this->setImage(":/images/ingame/button.png");
    Dice * dice = Dice::getInst();
    dice->roll();
}

DiceValuePanel::DiceValuePanel(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene,window)
{
    setValue(3);
}

void DiceValuePanel::setValue(int value)
{
    diceValue = value;
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


void DiceValuePanel::mousePressEvent(QGraphicsSceneMouseEvent *event){

}

void DiceValuePanel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}
