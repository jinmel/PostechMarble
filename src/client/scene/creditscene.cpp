#include "creditscene.h"
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QTimeLine>
#include <QMediaPlayer>
#include <QtGlobal>

CreditScene::CreditScene(qreal x, qreal y, qreal width,
            qreal height,
            QObject* parent)
 : QGraphicsScene(x,y,width,height,parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    Q_CHECK_PTR(this->window);

    setupCredit();
    animateCredit();
}

CreditScene::~CreditScene()
{

}

void CreditScene::switchToMain()
{
    qDebug() << "Switching to Main" << endl;
    window->switchScene(SceneType::MAIN);
}

void CreditScene::setupCredit()
{
    // load credit file
    credit = new QGameItem(this, window);
    credit->setImage(":images/credit/credit_background.png");
    credit->setPos(0, 0);

    // sound
    QMediaPlayer* sound = new QMediaPlayer();
    sound->setMedia(QUrl::fromLocalFile("D:/Development/C&C++/CSED232 Project/src/client/sound/error.mp3"));
    sound->setVolume(90);
    sound->play();
}

void CreditScene::animateCredit()
{
    /*QGraphicsItem* credit = this->items().value(0);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
    effect->setOpacity(0.0);

    credit->setGraphicsEffect(effect);

    QPropertyAnimation* animation = new QPropertyAnimation();*/
}
