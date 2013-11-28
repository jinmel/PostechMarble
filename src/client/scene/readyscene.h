#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"

class ReadyScene : public QGraphicsScene
{
    Q_OBJECT

private:
    MainWindow* window;
    QGameItem *background;

    void animateReady();
    void setupReady();

public:
    ReadyScene(qreal x=0, qreal y=0, qreal width=1280,
               qreal height=720, QObject *parent=0);
    ~ReadyScene();

public slots:
    void switchtoIngame();
};
