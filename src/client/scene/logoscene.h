#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"
#include <QObject>

class LogoScene : public QObject, public QGraphicsScene
{
    Q_OBJECT
private:
    MainWindow* window;

    QGameItem *back_logo;
    QGameItem *ok_test;
    QGameItem *team_logo;

    void animateLogo();
    void setupLogo();

public:
    LogoScene(qreal x=0,qreal y=0,qreal width=1280,
              qreal height=1280,
              QObject *parent=0);
    ~LogoScene();

public slots:
    void switchToMain();
};
