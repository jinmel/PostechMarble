#include "logoscene.h"
#include "types.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QtGlobal>


// Constructor & Destructor
LogoScene::LogoScene(qreal x, qreal y,
                      qreal width, qreal height,
                      QObject *parent)
 : QGraphicsScene(x,y,width,height,parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    Q_CHECK_PTR(this->window);

    setupLogo();
    animateLogo();
}


LogoScene::~LogoScene()
{

}


// Methods
void LogoScene::switchtoMain()
{
    qDebug() << "Switching to Main";
    window->switchScene(SceneType::MAIN);
}


void LogoScene::setupLogo()
{
    // setup for logo

    // set background
    QGameItem* background = new QGameItem(this, window);
    background->setImage(":images/logo/logo_background.png");
    background->setPos(0, 0);

    // set team_logo
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
    connect(animation,SIGNAL(finished()),this,SLOT(switchtoMain()));


    // play sound
    QMediaPlayer* sound = new QMediaPlayer();
    sound->setMedia(QUrl::fromLocalFile("D:/Development/C&C++/CSED232 Project/src/client/sound/logo_dang.mp3"));
    sound->setVolume(80);
    animation->start();
    sound->play();
}
