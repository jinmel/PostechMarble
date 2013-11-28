#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"

class MainScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void switchToReady();
private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *start_button;
    QGameItem *credit_button;

    void animateMain();
    void setupMain();
public:
    MainScene(qreal x=0,qreal y=0,qreal width=1280,
              qreal height=720,
              QObject *parent=0);
    ~MainScene();
};
