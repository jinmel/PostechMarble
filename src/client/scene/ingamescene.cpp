#include "ingamescene.h"
#include <QPixmap>
#include <QtGlobal>
#include "../dice.h"
#include <QTimeLine>
#include <QEasingCurve>
#include "../block.h"
#include "../localgame.h"
#include <QFileInfo>
#include <QGraphicsOpacityEffect>
#include "../pausepanel.h"
#include "../subjectblock.h"
#include <cstring>
#include "types.h"
#include <QVector>
#include "player.h"

IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent), window(dynamic_cast<MainWindow*>(parent))
{
    Q_CHECK_PTR(window);

    setBackgroundPixmap(":/images/ingame/board/background.png");
    LocalGame * game = LocalGame::getInst();
    Dice * dice = Dice::getInst();

    board = new Board(this,window);
    board->setPos(200,(720 - board->boundingRect().size().height())/2);
    board->setZValue(2);

    QVector<Player*> players = game->getPlayerQueue()->toVector();
    Player *player;

    foreach(player,players){
        addItem(player);
        player->setParent(board);
        player->setZValue(30);

        switch(player->getId()){
        case 1:
            status1 = new PlayerStatusDisplay(board,player);
            status1->setImage(":images/ingame/status/status1.png");
            status1->setPos(150, 120);
            break;
        case 2:
            status2 = new PlayerStatusDisplay(board,player);
            status2->setImage(":images/ingame/status/status2.png");
            status2->setPos(460, 120);
            break;
        case 3:
            status3 = new PlayerStatusDisplay(board,player);
            status3->setImage(":images/ingame/status/status3.png");
            status3->setPos(150, 250);
            break;
        case 4:
            status4 = new PlayerStatusDisplay(board,player);
            status4->setImage(":images/ingame/status/status4.png");
            status4->setPos(460, 250);
            break;
        }
    }

//    SubjectBlock * tmpblock = dynamic_cast<SubjectBlock*>(board->getBlock(10));
//    tmpblock->decideGrade();
//    player2->addBlock(tmpblock);
//    qDebug() << player2->hasBlock(tmpblock);

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
    dice_graphic->setPos(800,450);
    dice_graphic->setZValue(2);

    //주사위 패널 첫번째
    first_dice_panel = new DiceValuePanel(this,window);
    first_dice_panel->setPos(400,450);
    first_dice_panel->setZValue(2);

    //주사위 패널 두번째
    second_dice_panel = new DiceValuePanel(this,window);
    second_dice_panel->setPos(500,450);
    second_dice_panel->setZValue(2);

    // setup BGM
    bgm_player = new QMediaPlayer();
    bgm_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/GamePlay.mp3").absoluteFilePath()));
    bgm_player->setVolume(70);
    connect(bgm_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), bgm_player, SLOT(play()));

    game->init(board,Dice::getInst());

    //Signal / Slots connection
    connect(dice,SIGNAL(diceDouble()), this, SLOT(showDouble()));
    connect(dice,SIGNAL(firstDiceRolled(int)),first_dice_panel,SLOT(setValue(int)));
    connect(dice,SIGNAL(secondDiceRolled(int)),second_dice_panel,SLOT(setValue(int)));

}

IngameScene::~IngameScene(){
    delete first_dice_panel;
    delete second_dice_panel;
    delete dice_graphic;
    delete background;
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
    double_graphic->show(true, 300);
    double_timeline->start();
}

void IngameScene::hideDouble()
{
    double_graphic->hide(true, 300);
}


void IngameScene::animateIngame()
{
    QMediaPlayer *player = new QMediaPlayer();
    player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/gamestart.wav").absoluteFilePath()));
    player->play();
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
    timeline = new QTimeLine(20000); //showing photo in 20 seconds
    timeline->setFrameRange(0,8); // 3 spins + show and hide
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

    // show player type
    m_type_label = new QGameItem(this);
    m_type_label->setPos(130, 0);
    m_type_label->setZValue(3);
    m_type_label->setScale(0.3);
    switch(player->getType()) {
        using namespace CharacterType;
        case LOL:
            m_type_label->setImage(":images/ready/clol.png");
            break;
        case GENIUS:
            m_type_label->setImage(":images/ready/cgen.png");
            break;
        case HARD_WORKER:
            m_type_label->setImage(":images/ready/cdu.png");
            break;
        case OUTSIDER:
            m_type_label->setImage(":images/ready/cout.png");
            break;
        case ALCOHOLIC:
            m_type_label->setImage(":images/ready/calc.png");
            break;
     }

    // hide for default
    this->disable();

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

void PlayerStatusDisplay::setEnergyText(int energy){
    m_display_energy = energy;
    m_timeline->start();
}

void PlayerStatusDisplay::activate(){
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1.0);
    this->setGraphicsEffect(effect);
}


PlayerStatusDisplay::~PlayerStatusDisplay(){
    delete m_energy_label;
    delete m_timeline;
    delete m_type_label;
}

void PlayerStatusDisplay::disable(){
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.3);
    this->setGraphicsEffect(effect);
}
