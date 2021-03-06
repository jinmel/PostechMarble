#pragma once
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "../mainwindow.h"
#include "../qgameitem.h"

class LogoScene : public QGraphicsScene
{
    Q_OBJECT

private:
    MainWindow* window;
    QGameItem *background;
    QGameItem *team_logo;
    QMediaPlayer *effect_sound;

    void setupLogo();

public:
    LogoScene(qreal x=0, qreal y=0, qreal width=1280,
              qreal height=720, QObject *parent=0);
    ~LogoScene();
    void animateLogo();

public slots:
    void switchtoMain();
};
