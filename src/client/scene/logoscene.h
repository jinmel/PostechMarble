#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"


class LogoScene : public QGraphicsScene
{
private:
    MainWindow* window;

    QGameItem *back_logo;
    QGameItem *ok_test;
    QGameItem *team_logo;

    void animateLogo();
    void setupLogo();

public:
    LogoScene(MainWindow *window);
    ~LogoScene();

public slots:
    void switchToMain();
};
