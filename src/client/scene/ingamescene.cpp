#include "ingamescene.h"
#include <QPixmap>
#include <QtGlobal>
#include "../dice.h"
#include <QTimeLine>
#include <QEasingCurve>
#include "block.h"
#include "localgame.h"
#include <QFileInfo>


IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent), window(dynamic_cast<MainWindow*>(parent))
{
    Q_CHECK_PTR(window);

    setBackgroundPixmap(":/images/ingame/board/background.png");
    LocalGame * game = LocalGame::getInst();

    board = new Board(this,window);
    board->setPos(200,720 - board->boundingRect().size().height());
    board->setZValue(2);

    Player * player = new Player(board,1);
    player->setImage(":/images/ingame/pieces/blue.png");
    player->setPos(BlockCoords::corner_coord[0]);
    player->setZValue(3);
    game->addPlayer(player);

    player = new Player(board,2);
    player->setImage(":/images/ingame/pieces/red.png");
    player->setPos(BlockCoords::corner_coord[0]);
    player->setZValue(3);
    player->setEnergy(0);
    player->addBlock(board->getBlock(10));
    player->addBlock(board->getBlock(11));
    player->addBlock(board->getBlock(13));
    game->addPlayer(player);

    game->init(board,Dice::getInst());

    // double graphic: hide
    double_graphic = new QGameItem(this, window);
    double_graphic->setImage(":images/ingame/double.png");
    double_graphic->setPos(440, 300);
    double_graphic->setZValue(4);
    double_graphic->hide(false, 0);

    // timeline for double graphic
    double_timeline = new QTimeLine(1500);
    connect(double_timeline, SIGNAL(finished()), this, SLOT(hideDouble()));

    //주사위 그래픽
    dice_graphic = new DiceGraphicItem(this,window);
    dice_graphic->setPos(800,400);
    dice_graphic->setZValue(2);

    //주사위 패널 첫번째
    first_dice_panel = new DiceValuePanel(this,window);
    first_dice_panel->setPos(400,400);
    first_dice_panel->setZValue(2);

    //주사위 패널 두번째
    second_dice_panel = new DiceValuePanel(this,window);
    second_dice_panel->setPos(500,400);
    second_dice_panel->setZValue(2);

    status1 = new QGameItem(this, window);
    status1->setImage(":images/ingame/status/status1.png");
    status1->setPos(350, 160);
    status1->setZValue(2);

    status2 = new QGameItem(this, window);
    status2->setImage(":images/ingame/status/status2.png");
    status2->setPos(660, 160);
    status2->setZValue(2);

    // setup BGM
    bgm_player = new QMediaPlayer();
    bgm_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/bgm.mp3").absoluteFilePath()));

    //Signal / Slots connection
    Dice * dice = Dice::getInst();

    connect(dice,SIGNAL(diceDouble()), this, SLOT(showDouble()));
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
    background = this->addPixmap(QPixmap(filename));
    return background;
}

QGraphicsPixmapItem* IngameScene::backgroundPixmap(){
    return background;
}


void IngameScene::showDouble()
{
    qDebug() << "Show Double";
    double_graphic->show(true, 300);
    double_timeline->start();
}

void IngameScene::hideDouble()
{
    qDebug() << "Hide Double";
    double_graphic->hide(true, 300);
}


void IngameScene::animateIngame()
{
    QMediaPlayer *player = new QMediaPlayer();
    player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/gamestart.wav").absoluteFilePath()));
    player->play();

    //bgm_player->play();
}

// DiceGrahicItem
DiceGraphicItem::DiceGraphicItem(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene,window){
    //버튼 초기상태 이미지
    this->setImage(":/images/ingame/button.png");
}


void DiceGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //버튼이 눌렸을 때의 이미지로 바꿈
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


// DiceValuePanel
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


// PhotoGenicItem
PhotoGenicItem::PhotoGenicItem(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene,window){

}

void PhotoGenicItem::showPhotos(){
    timeline = new QTimeLine(12000); //spin for 3 second
    timeline->setFrameRange(0,8); // 3 spins
    timeline->setEasingCurve(QEasingCurve::Linear);
    connect(this->timeline,SIGNAL(frameChanged(int)),this,SLOT(slidePhoto(int)));
    connect(this->timeline,SIGNAL(finished()),this,SLOT(slideFinish()));
    timeline->start();
    setZValue(10);
    setPos(QPointF(1280/2,720/2) + QPointF(-200,-150));
    hide(false);
}

PhotoGenicItem::~PhotoGenicItem()
{
    qDebug()<<"photogenic item destoyed."<<endl;
}

void PhotoGenicItem::slidePhoto(int frame){
    switch(frame){
    case 1:
        setImage(":/images/ourphotos/photo1.png");
        show(true);
        break;
    case 2:
        hide(true);
        break;
    case 3:
        setImage(":/images/ourphotos/photo2.png");
        show(true);
        break;
    case 4:
        hide(true);
        break;
    case 5:
        setImage(":/images/ourphotos/photo3.png");
        show(true);
        break;
    case 6:
        hide(true);
        break;
    }
}

void PhotoGenicItem::slideFinish(){
    delete this;
}
