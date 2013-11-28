#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"

class MainScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void switchtoReady();
    void switchtoCredit();
private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *start_button;
    QGameItem *credit_button;

    void animateMain();
    void setupMain();
public:
    MainScene(qreal x=0, qreal y=0, qreal width=1280,
              qreal height=720, QObject *parent=0);
    ~MainScene();
};


class StartButton : public QGameItem
{
    Q_OBJECT
public:
    StartButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~StartButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


class CreditButton : public QGameItem
{
    Q_OBJECT
public:
    CreditButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~CreditButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
