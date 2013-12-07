#include "gameoverscene.h"
#include "../types.h"
#include "mainscene.h"
#include "qgameitem.h"
#include "localgame.h"
#include <QGraphicsItem>
#include <QDebug>

GameoverScene::GameoverScene(qreal x, qreal y,
                             qreal width, qreal height,
                             QObject *parent)
    :QGraphicsScene(x, y, width, height, parent)
{
    this->window = dynamic_cast<MainWindow*> (parent);
    if(this->window == NULL) qDebug()<<"window is null!";
    Q_CHECK_PTR(this->window);

    winner = LocalGame::getInst()->getWinner();

    qDebug()<<"hello";
    background = new QGameItem(this,this->window);
    credit_button = new QGameItem(this,this->window);
    player_pos = new QGameItem(this,this->window);
    winner_statement = new QGameItem(this,this->window);
    timeline = new QTimeLine(1000);

    timeline->setFrameRange(1,10);
    connect(timeline,SIGNAL(frameChanged(int)),this,SLOT(animateWinnerImage(int)));
    connect(timeline,SIGNAL(finished()),timeline,SLOT(start())); //run forever
    timeline->start();
    player_pos->setAcceptHoverEvents(true);

    setupGameover();
}

GameoverScene::~GameoverScene()
{
    delete background;
    delete credit_button;
}

void GameoverScene::setupGameover()
{
    //setup for gameover

    //set background
    background = new QGameItem(this, window);
    background->setImage(":/images/gameover/game_over_background.png");
    background->setPos(0,0);
    background->setZValue(0);

    //set winner image
    //background->setImage();

    //set credit button
    credit_button = new CreditButton(this, window);
    credit_button->setPos(635,580);

    /*switch(winner->getId())
   {
    case 1:
        player_pos = new QGameItem(this,window);
        player_pos->setImage(":/images/gameover/red_player.png");
        player_pos->setPos(100,100);
        player_pos->setZValue(100);
        qDebug()<<"what";
        break;
    case 2:
        player_pos = new QGameItem(this,window);
        player_pos->setImage(":/images/gameover/blue_player.png");
        player_pos->setPos(100,100);
        player_pos->setZValue(100);
        qDebug()<<"what";
        break;
    case 3:
        player_pos = new QGameItem(this,window);
        player_pos->setImage(":/images/gameover/green_player.png");
        player_pos->setPos(100,100);
        player_pos->setZValue(100);
        qDebug()<<"what";
        break;
    case 4:
        player_pos = new QGameItem(this,window);
        player_pos->setImage(":/images/gameover/yellow_player.png");
        player_pos->setPos(100,100);
        player_pos->setZValue(100);
        qDebug()<<"what";
        break;

    }*/

    switch(winner->getType())
    {
    case 1:
        winner_statement = new QGameItem(this,window);
        winner_statement->setImage(":/images/ready/clol.png");
        winner_statement->setPos(760,300);
        winner_statement->setScale(0.6);
        break;
    case 2:
        winner_statement = new QGameItem(this,window);
        winner_statement->setImage(":/images/ready/cgen.png");
        winner_statement->setPos(760,300);
        winner_statement->setScale(0.6);
        break;
    case 3:
        winner_statement = new QGameItem(this,window);
        winner_statement->setImage(":/images/ready/cdu.png");
        winner_statement->setPos(760,300);
        winner_statement->setScale(0.6);
        break;
    case 4:
        winner_statement = new QGameItem(this,window);
        winner_statement->setImage(":/images/ready/cout.png");
        winner_statement->setPos(760,300);
        winner_statement->setScale(0.6);
        break;
    case 5:
        winner_statement = new QGameItem(this,window);
        winner_statement->setImage(":/images/ready/calc.png");
        winner_statement->setPos(760,300);
        winner_statement->setScale(0.6);
        break;

    }

}

void GameoverScene::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    moving = true;
}

void GameoverScene::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    moving = false;
}

void GameoverScene::animateWinnerImage(int frame){


    player_pos->setScale(2.5);

    QString filename = QString(":/images/ingame/character/");

    filename += QString("top_down_");

    if(winner->getId() == 1 || winner->getId() == 3)
        filename += QString("io_");
    else if(winner->getId() == 2 || winner->getId() == 4)
        filename += QString("id_");

    filename += winner->getColor() + QString("_");

    if(moving)
        filename += QString("walk_");
    else
        filename += QString("stand_");

    filename += QString::number(frame).rightJustified(3,'0') + QString(".png");

    winner->setPixmap(QPixmap(filename));

    if(winner->getId() == 4)
        player_pos->setPos(QPointF(950,170));

    qDebug()<<"hello3";
}
