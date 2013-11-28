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
    animateMain();
}


MainScene::~MainScene()
{

}


// Methods
void MainScene::switchtoReady()
{
    qDebug() << "Switching to Ready" << endl;
    window->switchScene(SceneType::READY);
}


void MainScene::setupMain()
{
    // setup for main

    // set background
    background = new QGameItem(this, window);
    background->setImage(":images/main/main_background.png");
    background->setPos(0, 0);

    // set buttons
    StartButton *start_button = new StartButton(this, window);
    start_button->setImage(":/images/button_ok.png");
    start_button->setPos(600,500);

    CreditButton *credit_button = new CreditButton(this, window);
    credit_button->setImage(":/images/button_ok.png");
    credit_button->setPos(600,600);
}


void MainScene::animateMain()
{

}


// StartButton
StartButton::StartButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{

}

StartButton::~StartButton()
{

}

void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setPixmap(QPixmap(":images/button_ok_click.png"));

    // move to ready scene
    window->switchScene(SceneType::READY);
}

void StartButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(QPixmap(":images/button_ok.png"));
}


// CreditButton
CreditButton::CreditButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{

}

CreditButton::~CreditButton()
{

}

void CreditButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Credit button clicked.";
    setPixmap(QPixmap(":images/button_ok_click.png"));

    // move to ready scene
    window->switchScene(SceneType::CREDIT);
}

void CreditButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(QPixmap(":images/button_ok.png"));
}
