#include "mainscene.h"
#include "../types.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtGlobal>
#include <QFileInfo>


// Constructor & Destructor
MainScene::MainScene(qreal x, qreal y,
                      qreal width, qreal height,
                      QObject *parent)
 : QGraphicsScene(x,y,width,height,parent)
{
    this->window = dynamic_cast<MainWindow*>(parent);
    Q_CHECK_PTR(this->window);

    setupMain();
    connect(bgm_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), bgm_player, SLOT(play()));
}


MainScene::~MainScene()
{
    delete background;
    delete start_button;
    delete credit_button;
    delete gplus_button;
    delete fb_button;
    delete all;
    delete copy;
    delete bgm_player;

    qDebug() << "Main Scene Destroyed";
}


// Methods
void MainScene::setupMain()
{
    // setup for main

    // set background
    background = new QGameItem(this, window);
    background->setImage(":images/main/main_background.png");
    background->setPos(0, 0);

    // set buttons
    start_button = new StartButton(this, window);
    start_button->setPos(535,470);

    credit_button = new CreditButton(this, window);
    credit_button->setPos(535,560);

    gplus_button = new QGameItem(this, window);
    gplus_button->setImage(":images/main/social_g+.png");
    gplus_button->setPos(1080, 610);

    fb_button = new QGameItem(this, window);
    fb_button->setImage(":images/main/social_fb.png");
    fb_button->setPos(1170, 610);

    all = new QGameItem(this, window);
    all->setImage(":images/main/all.png");
    all->setPos(1175, 5);

    copy = new QGameItem(this, window);
    copy->setImage(":images/main/copy.png");
    copy->setPos(350, 690);

    // setup BGM
    bgm_player = new QMediaPlayer();
    bgm_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/postech_marble_bgm.mp3").absoluteFilePath()));
}


void MainScene::animateMain()
{
    bgm_player->play();
}


// StartButton
StartButton::StartButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    // 버튼 초기 이미
    this->setImage(":/images/main/button_main_start.png");
}

StartButton::~StartButton()
{

}

void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Start button clicked.";
    setImage(":images/main/button_main_start_pressed.png");
}

void StartButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/main/button_main_start.png");

    // move to ready scene
    window->switchScene(SceneType::READY);
}

void StartButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/main/button_main_start.png");
}


// CreditButton
CreditButton::CreditButton(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    // 버튼 초기 이미지
    this->setImage(":/images/main/button_main_credit.png");
}

CreditButton::~CreditButton()
{

}

void CreditButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Credit button clicked.";
    setImage(":images/main/button_main_credit_pressed.png");
}

void CreditButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/main/button_main_credit.png");

    // move to ready scene
    window->switchScene(SceneType::CREDIT);
}

void CreditButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/main/button_main_credit.png");
}
