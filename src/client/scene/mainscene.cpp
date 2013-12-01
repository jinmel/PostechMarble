#include "mainscene.h"
#include "../types.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtGlobal>


// Constructor & Destructor
MainScene::MainScene(qreal x, qreal y,
                      qreal width, qreal height,
                      QObject *parent)
 : QGraphicsScene(x,y,width,height,parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    Q_CHECK_PTR(this->window);

    setupMain();
}


MainScene::~MainScene()
{
    delete background;
    delete start_button;
    delete credit_button;
}


// Methods
void MainScene::setupMain()
{
    // setup for main

    // set background
    background = new QGameItem(this, window);
    background->setImage(":images/main/main_background.png");
    background->setPos(0, 0);

    // set buttons
    start_button = new StartButton(this, window);
    start_button->setPos(535,500);

    credit_button = new CreditButton(this, window);
    credit_button->setPos(535,590);
}


void MainScene::animateMain()
{

}


// StartButton
StartButton::StartButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    // 버튼 초기 이미
    this->setImage(":/images/main/button_main_start.png");
}

StartButton::~StartButton()
{

}

void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setImage(":images/main/button_main_start_press.png");
}

void StartButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/main/button_main_start.png");

    // move to ready scene
    window->switchScene(SceneType::READY);
    //window->animateScene(SceneType::READY);
}

void StartButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/main/button_main_start.png");
}


// CreditButton
CreditButton::CreditButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    // 버튼 초기 이미지
    this->setImage(":/images/main/button_main_credit.png");
}

CreditButton::~CreditButton()
{

}

void CreditButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Credit button clicked.";
    setImage(":images/main/button_main_credit_pressed.png");
}

void CreditButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/main/button_main_credit.png");

    // move to ready scene
    window->switchScene(SceneType::CREDIT);
    window->animateScene(SceneType::CREDIT);
}

void CreditButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/main/button_main_credit.png");
}
