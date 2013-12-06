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

void GameoverScene::setupGameover(int winner)
{
    //setup for gameover

    //set background
    background = new QGameItem(this, window);
    background->setImage(":/images/gameover/game_over_background");
    background->setPos(0,0);

    switch(winner)
  {
    case 0:
        player_pos = new QGameItem(this, window);
        player_pos->setImage(":/images/gameover/red_player.png");
        player_pos->setPos(100,100);
        break;
    case 1:
        player_pos = new QGameItem(this, window);
        player_pos->setImage(":/images/gameover/blue_player.png");
        player_pos->setPos(100,100);
        break;
    case 2:
        player_pos = new QGameItem(this, window);
        player_pos->setImage(":/images/gameover/green_player.png");
        player_pos->setPos(100,100);
        break;
    case 3:
        player_pos = new QGameItem(this, window);
        player_pos->setImage(":/images/gameover/yellow_player.png");
        player_pos->setPos(100,100);
        break;
   }




    QGameItem *credit_button;
    QGameItem *player_pos;
    QGameItem *winner_statement;
    //set winner image
    //background->setImage();

    //set credit button
    credit_button = new CreditButton(this, window);
    credit_button->setPos(535,470);


}
