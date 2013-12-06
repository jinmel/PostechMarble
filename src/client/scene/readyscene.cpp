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
    player_image1->setPos(150,200);
    player_image2->setPos(400,200);
    player_image3->setPos(650,200);
    player_image4->setPos(900,200);


}

ReadyScene::~ReadyScene()
{
    delete ready_button;
    delete background;
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


    window->switchScene(SceneType::INGAME);
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
    setPixmap(QPixmap(":/images/ready/plus.png"));
    setScale(2.5);
}

ReadyPlayerImage::~ReadyPlayerImage(){

}

void ReadyPlayerImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!play)
        setPixmap(QPixmap(":/images/ready/plus_pressed.png"));
}

void ReadyPlayerImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!play){
        play = true;
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

void ReadyPlayerImage::animatePlayerImage(int frame){
    if(!play){//not playing. don't show player image
        return;
    }

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
        setPos(QPointF(900,180));
}



