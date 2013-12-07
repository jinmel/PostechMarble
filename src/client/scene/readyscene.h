#pragma once
#include <QGraphicsScene>
#include "../mainwindow.h"
#include "../qgameitem.h"
#include "player.h"

// Ingame Scene으로 가는 버튼
class ReadyButton;
class ReadyPlayerImage;

class ReadyScene : public QGraphicsScene
{
    Q_OBJECT

private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *ready_button;
    Player * player1;
    Player * player2;
    Player * player3;
    Player * player4;
    ReadyPlayerImage * player_image1;
    ReadyPlayerImage * player_image2;
    ReadyPlayerImage * player_image3;
    ReadyPlayerImage * player_image4;
    void setupReady();
public:
    ReadyScene(qreal x=0, qreal y=0, qreal width=1280,
               qreal height=720, QObject *parent=0);
    ~ReadyScene();
    ReadyPlayerImage * getPlayerImage(int player_id);

    void animateReady();
};


class ReadyButton : public QGameItem
{
    Q_OBJECT
public:
    ReadyButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~ReadyButton();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class ReadyPlayerImage : public QGameItem
{
    Q_OBJECT
private:
    Player * player;
    bool moving;
    bool play;
    int type;
    QTimeLine * timeline;
    QGameItem * name;
    QGameItem * explain;
public:
    ReadyPlayerImage(QGraphicsScene * scene, MainWindow * window,Player * player);
    virtual ~ReadyPlayerImage();
    void setPlay(bool play);
    bool getPlay();
    Player * getPlayer();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
public slots:
    void animatePlayerImage(int frame);
};

