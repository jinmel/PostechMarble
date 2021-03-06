#include "readyscene.h"
#include "../types.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtGlobal>
#include "localgame.h"
#include <QMessageBox>
#include "qgameitem.h"

// Constructor & Destructor
ReadyScene::ReadyScene(qreal x, qreal y,
                       qreal width, qreal height,
                       QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    if(this->window == NULL) qDebug() <<"window is null!";
    Q_CHECK_PTR(this->window);

    // setup Ready Scene
    setupReady();

    //first setup two players

    player1 = new Player(NULL,1);
    player2 = new Player(NULL,2);
    player3 = new Player(NULL,3);
    player4 = new Player(NULL,4);
    player_image1 = new ReadyPlayerImage(this,window,player1);
    player_image2 = new ReadyPlayerImage(this,window,player2);
    player_image3 = new ReadyPlayerImage(this,window,player3);
    player_image4 = new ReadyPlayerImage(this,window,player4);
    player_image1->setPos(50,200);
    player_image2->setPos(350,200);
    player_image3->setPos(650,200);
    player_image4->setPos(950,200);
}

ReadyScene::~ReadyScene()
{
    delete ready_button;
    delete background;
}

ReadyPlayerImage * ReadyScene::getPlayerImage(int player_id){
    switch(player_id){
    case 1:
        return player_image1;
    case 2:
        return player_image2;
    case 3:
        return player_image3;
    case 4:
        return player_image4;
    }
}

Player * ReadyScene::getPlayer(int player_id){
    switch(player_id){
    case 1:
        return player1;
    case 2:
        return player2;
    case 3:
        return player3;
    case 4:
        return player4;
    }
}

Player * ReadyPlayerImage::getPlayer(){
    return this->player;
}

// Methods
void ReadyScene::setupReady()
{
	// setup for ready

    // set background
    background = new QGameItem(this, window);
    background->setImage(":images/ready/readyscene.png");
    background->setPos(0, 0);

    // set buttons
    ready_button = new ReadyButton(this, window);
    ready_button->setPos(1185,20);
}


void ReadyScene::animateReady()
{

}

// ReadyButton
ReadyButton::ReadyButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    setImage(":images/ingame/pause/resume.png");
}

ReadyButton::~ReadyButton()
{

}

void ReadyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setImage(":images/ingame/pause/resume_pressed.png");
}

void ReadyButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/ingame/pause/resume.png");

    // move to ready scene

    //ReadyScene * rscene = scene();

    ReadyScene * rscene = dynamic_cast<ReadyScene*>(scene());

    qDebug() <<  LocalGame::getInst()->getPlayerCount();

    if(LocalGame::getInst()->getPlayerCount() < 2){
        QMessageBox warn_box;
        warn_box.setStandardButtons(QMessageBox::Ok);
        warn_box.setDefaultButton(QMessageBox::Ok);
        warn_box.setText("2명 이상의 플레이어가 필요합니다.");
        warn_box.exec();
        return;
    }
    else{
        LocalGame::getInst()->debugPrintAllPlayers();
        window->switchScene(SceneType::INGAME);
    }
}

void ReadyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/ingame/pause/resume_pressed.png");
}

ReadyPlayerImage::ReadyPlayerImage(QGraphicsScene * scene,MainWindow* window,Player * player)
    : QGameItem(scene,window),player(player),moving(false),play(false)
{
    timeline = new QTimeLine(1000);
    timeline->setFrameRange(1,10);
    connect(timeline,SIGNAL(frameChanged(int)),this,SLOT(animatePlayerImage(int)));
    connect(timeline,SIGNAL(finished()),timeline,SLOT(start())); //run forever
    timeline->start();
    setAcceptHoverEvents(true);
    setPixmap(QPixmap(":/images/ready/plus_big.png"));
    name = new QGameItem(scene, window);
    name->setImage(":images/ready/inv.png");
    name->setScale(0.5);
    explain = new QGameItem(scene, window);
    explain->setImage(":images/ready/inv.png");
    explain->setScale(0.27);
    if(player->getId()==1){
        name->setPos(50,500);
        explain->setPos(50,600);
    }
    else if(player->getId()==2){
        name->setPos(350,500);
        explain->setPos(350,600);
    }
    else if(player->getId()==3){
        name->setPos(650,500);
        explain->setPos(650,600);
    }
    else if(player->getId()==4){
        name->setPos(950,500);
        explain->setPos(950,600);
    }
}

ReadyPlayerImage::~ReadyPlayerImage(){

}

void ReadyPlayerImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!play)
        setPixmap(QPixmap(":/images/ready/plus_big_pressed.png"));
}

void ReadyPlayerImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!play){
        switch(player->getType()){
        case CharacterType::LOL:
            name->setPixmap(QPixmap(":/images/ready/clol.png"));
            explain->setPixmap(QPixmap(":/images/ready/elol.png"));
            break;
        case CharacterType::GENIUS:
            name->setPixmap(QPixmap(":/images/ready/cgen.png"));
            explain->setPixmap(QPixmap(":/images/ready/egen.png"));
            break;
        case CharacterType::HARD_WORKER:
            name->setPixmap(QPixmap(":/images/ready/cdu.png"));
            explain->setPixmap(QPixmap(":/images/ready/edu.png"));
            break;
        case CharacterType::OUTSIDER:
            name->setPixmap(QPixmap(":/images/ready/cout.png"));
            explain->setPixmap(QPixmap(":/images/ready/eout.png"));
            break;
        case CharacterType::ALCOHOLIC:
            name->setPixmap(QPixmap(":/images/ready/calc.png"));
            explain->setPixmap(QPixmap(":/images/ready/ealc.png"));
        }
        play = true;
        LocalGame::getInst()->addPlayer(player);
    }
}

void ReadyPlayerImage::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    moving = true;
}

void ReadyPlayerImage::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    moving = false;
}

void ReadyPlayerImage::setPlay(bool play){
    this->play = play;
}

bool ReadyPlayerImage::getPlay(){
    return play;
}

void ReadyPlayerImage::animatePlayerImage(int frame){
    if(!play){//not playing. don't show player image
        return;
    }

    setScale(2.5);

    QString filename = QString(":/images/ingame/character/");

    filename += QString("top_down_");

    if(player->getId() == 1 || player->getId() == 3)
        filename += QString("io_");
    else if(player->getId() == 2 || player->getId() == 4)
        filename += QString("id_");

    filename += player->getColor() + QString("_");

    if(moving)
        filename += QString("walk_");
    else
        filename += QString("stand_");

    filename += QString::number(frame).rightJustified(3,'0') + QString(".png");

    setPixmap(QPixmap(filename));

    if(player->getId() == 4)
        setPos(QPointF(950,170));
}



