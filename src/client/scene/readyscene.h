#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"

// Ingame Scene으로 가는 버튼
class ReadyButton;

class ReadyScene : public QGraphicsScene
{
    Q_OBJECT

private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *ready_button;

    void setupReady();

public:
    ReadyScene(qreal x=0, qreal y=0, qreal width=1280,
               qreal height=720, QObject *parent=0);
    ~ReadyScene();
    void animateReady();
};


class ReadyButton : public QGameItem
{
    Q_OBJECT
public:
    ReadyButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~ReadyButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};