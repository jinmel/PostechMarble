#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"

class LogoScene :  public QGraphicsScene
{
    Q_OBJECT
public slots:
    void switchToMain();
private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *team_logo;

    void animateLogo();
    void setupLogo();

public:
    LogoScene(qreal x=0,qreal y=0,qreal width=1280,
              qreal height=1280,
              QObject *parent=0);
    ~LogoScene();

};
