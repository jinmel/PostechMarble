#pragma once
#include <QGraphicsScene>
#include "../mainwindow.h"
#include "../qgameitem.h"

// Ready Scene으로 가는 버튼
class StartButton;
// Credit Scene으로 가는 버튼
class CreditButton;

class MainScene : public QGraphicsScene
{
    Q_OBJECT

private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *start_button;
    QGameItem *credit_button;
    QGameItem *gplus_button;
    QGameItem *fb_button;
    QGameItem *all;

    void setupMain();

public:
    MainScene(qreal x=0, qreal y=0, qreal width=1280,
              qreal height=720, QObject *parent=0);
    ~MainScene();
    void animateMain();
};


class StartButton : public QGameItem
{
    Q_OBJECT
public:
    StartButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~StartButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};


class CreditButton : public QGameItem
{
    Q_OBJECT
public:
    CreditButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~CreditButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};
