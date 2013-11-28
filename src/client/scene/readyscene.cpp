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
    Q_CHECK_PTR(this->window);

    setupReady();
    animateReady();
}

ReadyScene::~ReadyScene()
{

}


void ReadyScene::setupReady()
{

}


void ReadyScene::animateReady()
{

}

void ReadyScene::switchtoIngame()
{

}
