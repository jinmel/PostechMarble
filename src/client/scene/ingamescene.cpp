#include "ingamescene.h"
#include <QPixmap>
#include <QtGlobal>
#include "dice.h"
#include <QTimeLine>
#include <QEasingCurve>


IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent), window(dynamic_cast<MainWindow*>(parent))
{
    Q_CHECK_PTR(window);

    setBackgroundPixmap(":/images/ingame/background_test.jpg");

    board = new Board(this,window);
    board->setPos(200,10);
    qDebug() << board->image()->size();

    //주사위 그래픽
    dice_graphic = new DiceGraphicItem(this,window);
    dice_graphic->setPos(900,400);
    dice_graphic->setZValue(2);

    //주사위 패널 첫번째
    first_dice_panel = new DiceValuePanel(this,window);
    first_dice_panel->setPos(400,400);
    first_dice_panel->setZValue(2);
    //주사위 패널 두번째
    second_dice_panel = new DiceValuePanel(this,window);
    second_dice_panel->setPos(500,400);
    second_dice_panel->setZValue(2);



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

void DiceGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //hover event
    this->setImage(":/images/ingame/button2.png");
}

void DiceGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //버튼이 눌렸을 때의 이미지로 바꿈

    qDebug() << "dice button Pressed";
    this->setImage(":/images/ingame/button2_pushed.png");
    //QGameItem::mousePressEvent(event);

}

void DiceGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //마우스에서 땠을 경우 다시 초기상태 이미지로 바꿈
    this->setImage(":/images/ingame/button.png");
    //여기에 게임 스테이트 머신을 추가해서 롤할지 안할지 결정하게 해야함
    Dice * dice = Dice::getInst();
    dice->roll();

}

DiceValuePanel::DiceValuePanel(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene,window)
{
    setImage(":/images/ingame/dice/dice3.png"); //default image
    timeline = new QTimeLine(1500); //spin for 1.5 second
    timeline->setFrameRange(0,50); // 50 spins
    timeline->setEasingCurve(QEasingCurve::InOutCirc);
    connect(this->timeline,SIGNAL(frameChanged(int)),this,SLOT(spinValue(int)));
    connect(timeline,SIGNAL(finished()),this,SLOT(endSpin()));
}

void DiceValuePanel::endSpin(){
    //finally fix dice image to diceValue
    switch(diceValue){
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

void DiceValuePanel::setValue(int value){
    diceValue = value;
    timeline->start();
}

void DiceValuePanel::spinValue(int frame){
    int value = rand() % 6 + 1;
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
