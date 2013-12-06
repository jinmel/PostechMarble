#include "readyscene.h"
#include "../types.h"
#include "../dice.h"
#include "../localgame.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtGlobal>


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
}

ReadyScene::~ReadyScene()
{
    delete background;
    delete ready_button;
    delete player_types;
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
    ready_button->setPos(530,500);

    player_num = 3;
    player_types = new int[player_num];

    Dice::getInst();
    LocalGame *localgame = LocalGame::getInst();

    for(int index=0; index < player_num; index++) {
        player_types[index] = rand() % 5;
        Player * new_player = new Player(NULL,1, player_types[index]);
        new_player->setImage(":/images/ingame/pieces/blue.png");
        new_player->setZValue(3);
        localgame->addPlayer(new_player);
    }
}


void ReadyScene::animateReady()
{

}

// ReadyButton
ReadyButton::ReadyButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    setImage(":images/ready/button_start.png");
}

ReadyButton::~ReadyButton()
{

}

void ReadyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setImage(":images/ready/button_start_pressed.png");
}

void ReadyButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/ready/button_start.png");

    // move to ready scene
    window->switchScene(SceneType::INGAME);
}

void ReadyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/ready/button_start.png");
}
