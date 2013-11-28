#include "creditscene.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QTimeLine>
#include <QMediaPlayer>
#include <QtGlobal>

CreditScene::CreditScene(qreal x=0, qreal y=0, qreal width=1280,
            qreal height=720,
            QObject* parent=0)
    : QGraphicsScene(x,y,width,height,parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    Q_CHECK_PTR(this->window);

    setupCredit();
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
    credit->setImage(":images/ingame/background.png");
    credit->setPos(0, 0);

    // sound
    QMediaPlayer* sound = new QMediaPlayer();
    sound->setMedia(QUrl::fromLocalFile("D:/Development/C&C++/CSED232 Project/src/client/sound/error.mp3"));
    sound->setVolume(90);
    sound->play();
}
