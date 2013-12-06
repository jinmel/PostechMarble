#include "gameoverscene.h"
#include "../types.h"
#include <QGraphicsItem>
#include <QDebug>

GameoverScene::GameoverScene(qreal x, qreal y,
                             qreal width, qreal height,
                             QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    this->window = dynamic_cast<MainWindow*> (parent);
    if(this->window == NULL) qDebug()<<"window is null!";
    Q_CHECK_PTR(this->window);

    //setupGameover();
}

GameoverScene::~GameoverScene()
{
    delete ready_button;
}

/*





*/
