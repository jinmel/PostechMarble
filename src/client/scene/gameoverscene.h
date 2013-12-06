#pragma once
#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <QGraphicsScene>
#include "../mainwindow.h"
#include "../qgameitem.h"

class GameoverScene : public QGraphicsScene
{
    Q_OBJECT
private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *ready_button;

    void setupGameover();

public:
    explicit GameoverScene(qreal x=0, qreal y=0, qreal width=1280,
                           qreal height=720, QObject *parent = 0);
    ~GameoverScene();

signals:

public slots:

};

#endif // GAMEOVERSCENE_H
