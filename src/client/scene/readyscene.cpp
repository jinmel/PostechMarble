#include "readyscene.h"
#include "types.h"
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
    delete ready_button;
}



// Methods
void ReadyScene::setupReady()
{
	// setup for ready

    // set background
    background = new QGameItem(this, window);
    background->setImage(":images/main/main_background.png");
    background->setPos(0, 0);

    // set buttons
    ready_button = new ReadyButton(this, window);
    ready_button->setImage(":/images/button_ok.png");
    ready_button->setPos(600,500);
}


void ReadyScene::animateReady()
{

}

// ReadyButton
ReadyButton::ReadyButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{

}

ReadyButton::~ReadyButton()
{

}

void ReadyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setImage(":images/button_ok_click.png");
}

void ReadyButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/button_ok.png");

    // move to ready scene
    window->switchScene(SceneType::INGAME);
    //window->animateScene(SceneType::INGAME);
}

void ReadyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/button_ok.png");
}
