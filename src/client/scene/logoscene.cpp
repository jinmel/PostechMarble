#include "logoscene.h"
#include "types.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMediaPlayer>


LogoScene::LogoScene(qreal x, qreal y,
                      qreal width, qreal height,
                      QObject *parent)
 : QGraphicsScene(x,y,width,height, parent)
{
    this->window = (MainWindow*)parent;

    setupLogo();
    animateLogo();
}


LogoScene::~LogoScene()
{

}


void LogoScene::switchToMain()
{
    qDebug() << "Switching to Main" << endl;
    window->switchScene(SceneType::MAIN);
}


void LogoScene::setupLogo()
{
    // setup for logo
    back_logo = new QGameItem(this, window);
    back_logo->setImage(":images/logo/logo_background.png");
    back_logo->setPos(0, 0);

    ok_test = new QGameItem(this, window);
    ok_test->setImage(":/images/button_ok.png");
    ok_test->setPos(600, 550);

    team_logo = new QGameItem(this, window);
    team_logo->setImage(":images/logo/team_logo.png"); //900 170
    team_logo->setPos(190, 275);
}


void LogoScene::animateLogo()
{
    QGraphicsItem* team_logo = this->items().value(0);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.0);

    team_logo->setGraphicsEffect(opacityEffect);

    QPropertyAnimation * animation = new QPropertyAnimation();
    animation->setTargetObject(opacityEffect);
    animation->setPropertyName("opacity");
    animation->setDuration(2000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    // connect: switch to main when logo animation finished
    connect(animation, SIGNAL(finished()), this, SLOT(switchToMain()));

    QMediaPlayer* sound = new QMediaPlayer();
    sound->setMedia(QUrl::fromLocalFile("D:/Development/C&C++/CSED232 Project/src/client/sound/logo_dang.mp3"));
    sound->setVolume(80);
    animation->start();
    sound->play();
}
