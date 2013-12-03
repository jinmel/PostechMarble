#include "creditscene.h"
#include "../types.h"
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QtGlobal>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QKeyEvent>


// Constructor & Destructor
CreditScene::CreditScene(qreal x, qreal y, qreal width,
            qreal height,
            QObject* parent)
 : QGraphicsScene(x,y,width,height,parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    if(this->window == NULL) qDebug() <<"window is null!";
    Q_CHECK_PTR(this->window);

    setupCredit();
}

CreditScene::~CreditScene()
{

}


// Methods
void CreditScene::switchToMain()
{
    qDebug() << "Switching to Main";
    window->switchScene(SceneType::MAIN);
}

void CreditScene::setupCredit()
{
    // load splash logo
    splash_logo = new QGameItem(this, window);
    splash_logo->setImage(":images/credit/credit_splash.png");
    splash_logo->setPos(0, 0);

    // load credit file
    credit = new Credit(this, window);
    credit->setPos(0, 0);
}

void CreditScene::animateCredit()
{
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.0);

    credit->setGraphicsEffect(opacityEffect);

    QPropertyAnimation* animation = new QPropertyAnimation();
    animation->setTargetObject(opacityEffect);
    animation->setPropertyName("opacity");
    animation->setDuration(3000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    // sound
    QMediaPlayer* player = new QMediaPlayer();
    player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/error.mp3").absoluteFilePath()));
    player->setVolume(80);
    
    // play sound & animate
    animation->start();
    player->play();
}

Credit::Credit(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    qDebug() << "load";
    this->setImage(":/images/credit/credit_background.png");
}

Credit::~Credit()
{

}

void Credit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Credit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // move to main
    window->switchScene(SceneType::MAIN);
}
