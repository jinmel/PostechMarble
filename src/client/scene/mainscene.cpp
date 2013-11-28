#include "mainscene.h"
#include "types.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMediaPlayer>
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
void MainScene::switchToReady()
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
    QGameItem *start_button = new QGameItem(this, window);
    start_button->setImage(":/images/button_ok.png");
    start_button->setPos(600,400);

    QGameItem *credit_button = new QGameItem(this, window);
    credit_button->setImage(":/images/button_ok.png");
    credit_button->setPos(600,500);
}


void MainScene::animateMain()
{

}
