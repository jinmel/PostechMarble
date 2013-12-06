#include "gameoverscene.h"
#include "../types.h"
#include "mainscene.h"
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
    delete credit_button;
}

void GameoverScene::setupGameover()
{
    //setup for gameover

    //set background
    background = new QGameItem(this, window);
    background->setImage(":/images/gameover/gameover_background");
    background->setPos(0,0);

<<<<<<< HEAD
    //set credit button
    credit_button = new CreditButton(this, window);
    credit_button->setPos(535,470);

}



=======
    //set winner image
    //background->setImage();
}
>>>>>>> 55a54d1cb7458164f2c93e00d2f939c4049102ea
