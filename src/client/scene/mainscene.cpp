#include "mainscene.h"
#include "types.h"
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
    start_button->setPos(600,500);

    credit_button = new CreditButton(this, window);
    credit_button->setPos(600,600);
}


void MainScene::animateMain()
{

}


// StartButton
StartButton::StartButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    // 버튼 초기 이미
    this->setImage(":/images/button_ok.png");
}

StartButton::~StartButton()
{

}

void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setImage(":images/button_ok_click.png");
}

void StartButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/button_ok.png");

    // move to ready scene
    window->switchScene(SceneType::READY);
    //window->animateScene(SceneType::READY);
}

void StartButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/button_ok.png");
}


// CreditButton
CreditButton::CreditButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    // 버튼 초기 이미지
    this->setImage(":/images/button_ok.png");
}

CreditButton::~CreditButton()
{

}

void CreditButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Credit button clicked.";
    setImage(":images/button_ok_click.png");
}

void CreditButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/button_ok.png");

    // move to ready scene
    window->switchScene(SceneType::CREDIT);
    window->animateScene(SceneType::CREDIT);
}

void CreditButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/button_ok.png");
}
