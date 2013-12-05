#include "ingamescene.h"
#include <QPixmap>
#include <QtGlobal>
#include "../dice.h"
#include <QTimeLine>
#include <QEasingCurve>
#include "block.h"
#include "localgame.h"
#include <QFileInfo>
#include <QGraphicsOpacityEffect>
#include "pausepanel.h"
#include "subjectblock.h"
#include <cstring>


IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent), window(dynamic_cast<MainWindow*>(parent))
{
    Q_CHECK_PTR(window);

    setBackgroundPixmap(":/images/ingame/board/background.png");
    LocalGame * game = LocalGame::getInst();

    board = new Board(this,window);
    board->setPos(200,(720 - board->boundingRect().size().height())/2);
    board->setZValue(2);

    Player * player1 = new Player(board,1);
    player1->setImage(":/images/ingame/pieces/blue.png");
    player1->setZValue(3);


    Player * player2 = new Player(board,2);
    player2->setImage(":/images/ingame/pieces/red.png");
    player2->setZValue(3);
    player2->setEnergy(0);
    SubjectBlock * tmpblock = dynamic_cast<SubjectBlock*>(board->getBlock(10));
    tmpblock->decideGrade();
    player2->addBlock(tmpblock);
    qDebug() << player2->hasBlock(tmpblock);

    // pause panel
    pause_panel = new PausePanel(this, window);
    pause_panel->setPos(440, 280);
    pause_panel->setZValue(20);
    pause_panel->hide(false);

    // pause button
    pause_button = new PauseButton(this, window, pause_panel);
    pause_button->setPos(1200, 10);
    pause_button->setZValue(2);

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

    status1 = new PlayerStatusDisplay(board,player1);
    status1->setImage(":images/ingame/status/status1.png");
    status1->setPos(150, 120);
    status2 = new PlayerStatusDisplay(board,player2);
    status2->setImage(":images/ingame/status/status2.png");
    status2->setPos(460, 120);

    // setup BGM
    bgm_player = new QMediaPlayer();
    bgm_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/bgm.mp3").absoluteFilePath()));
    game->addPlayer(player1);
    game->addPlayer(player2);
    game->init(board,Dice::getInst());

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
    delete board;
    delete double_timeline;
    delete bgm_player;
    delete pause_button;
    delete pause_panel;
    LocalGame::delInst();
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
    //roll dice only when localgame state permits this
    if(LocalGame::getInst()->getGameState() == LocalGameState::ROLL_DICE){
        Dice * dice = Dice::getInst();
        dice->roll();
    }
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
    int randomvalue= rand()%3 + 1;
    QString folderstring=QString(":/images/ourphotos/set");
    QString numberstring=QString::number(randomvalue);
    QString filestring1=QString("/photo1.png");
    QString filestring2=QString("/photo2.png");
    QString filestring3=QString("/photo3.png");
    QString filestring11=folderstring+numberstring+filestring1;
    QString filestring22=folderstring+numberstring+filestring2;
    QString filestring33=folderstring+numberstring+filestring3;
    image1 = QPixmap(filestring11);
    image2 = QPixmap(filestring22);
    image3 = QPixmap(filestring33);
}

void PhotoGenicItem::showPhotos(){
    timeline = new QTimeLine(20000); //spin for 3 second
    timeline->setFrameRange(0,8); // 3 spins
    timeline->setEasingCurve(QEasingCurve::Linear);
    connect(this->timeline,SIGNAL(frameChanged(int)),this,SLOT(slidePhoto(int)));
    connect(this->timeline,SIGNAL(finished()),this,SLOT(slideFinish()));
    connect(this->timeline,SIGNAL(finished()),LocalGame::getInst(),SLOT(generalEvent()));
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
        setPixmap(image1);
        show(true);
        break;
    case 2:
        hide(true);
        break;
    case 3:
        setPixmap(image2);
        show(true);
        break;
    case 4:
        hide(true);
        break;
    case 5:
        setPixmap(image3);
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

PlayerStatusDisplay::PlayerStatusDisplay(QGameItem *parent,Player * player)
    : QGameItem(parent),m_player(player)
{
    m_energy_label = new QGraphicsTextItem(this);
    m_energy_label->setPos(170,55);
    m_energy_label->setZValue(100);
    m_timeline = new QTimeLine(1000,this);
    m_timeline->setFrameRange(0,20); //20 changes
    m_last_energy = player->getEnergy();
    QString labelhtml("<h1><font face='나눔고딕'>" + QString::number(player->getEnergy()) + "</font></h1>");
    m_energy_label->setHtml(labelhtml);

    //connect all signals and slots
    connect(m_timeline,SIGNAL(finished()),this,SLOT(endSpin()));
    connect(m_timeline,SIGNAL(frameChanged(int)),this,SLOT(spinNumber(int)));
    connect(player,SIGNAL(activate()),this,SLOT(activate()));
    connect(player,SIGNAL(disable()),this,SLOT(disable()));
    connect(player,SIGNAL(energyChanged(int)),this,SLOT(setEnergyText(int)));

}

void PlayerStatusDisplay::spinNumber(int frame){
    int spin_num = (((m_display_energy - m_last_energy) / 20) * frame) + m_last_energy;
    QString labelhtml("<h1><font face='나눔고딕'>" + QString::number(spin_num) + "</font></h1>");
    m_energy_label->setHtml(labelhtml);
}

void PlayerStatusDisplay::endSpin(){
    //finally determine energy display value
    QString labelhtml("<h1><font face='나눔고딕'>" + QString::number(this->m_display_energy) + "</font></h1>");
    m_energy_label->setHtml(labelhtml);
    m_last_energy = m_display_energy;
}

PlayerStatusDisplay::~PlayerStatusDisplay(){
    qDebug() << "called";
    delete m_energy_label;
    delete m_timeline;
    delete m_player;
}

void PlayerStatusDisplay::setEnergyText(int energy){
    qDebug() << "display energy :" << energy;
    qDebug() << "start energy:" << m_last_energy;
    m_display_energy = energy;
    m_timeline->start();
}

void PlayerStatusDisplay::activate(){
    qDebug() << "active";
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1.0);
    this->setGraphicsEffect(effect);
}

void PlayerStatusDisplay::disable(){
    qDebug() <<"disable";
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.3);
    this->setGraphicsEffect(effect);
}






