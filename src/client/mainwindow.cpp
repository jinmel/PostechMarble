#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgameitem.h"
#include "scene/creditscene.h"
#include "scene/logoscene.h"
#include "scene/mainscene.h"
#include "scene/ingamescene.h"
#include "scene/readyscene.h"
#include "scene/gameoverscene.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMediaPlayer>


// Constructor & Destructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = NULL;
    old_scene = NULL;
    delete_delay = new QTimeLine(100);
    connect(delete_delay, SIGNAL(finished()), this, SLOT(deleteOldScene()));

    switchScene(SceneType::LOGO);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete delete_delay;
}

// Methods
// Utility Functions
void MainWindow::switchScene(int scenetype)
{
    old_scene = scene;
    using namespace SceneType;
    switch(scenetype) {
        case LOGO:
            scene = new LogoScene(0, 0, 1280, 720, this);
            break;
        case MAIN:
            scene = new MainScene(0, 0, 1280, 720, this);
            break;
        case READY:
            scene = new ReadyScene(0, 0, 1280, 720, this);
            break;
        case INGAME:
            scene = new IngameScene(0, 0, 1280, 720, this);
            break;
        case GAMEOVER:
            scene = new GameoverScene(0, 0, 1280, 720, this);
            break;
        case CREDIT:
            scene = new CreditScene(0, 0, 1280, 720, this);
            break;
    }

    ui->graphicsView->setScene(scene);
    delete_delay->start();
    this->animateScene(scenetype);
}


void MainWindow::setApplication(QApplication* app)
{
    this->app = app;
}


void MainWindow::animateScene(int scenetype)
{
    using namespace SceneType;

    switch(scenetype) {
        case LOGO:
            dynamic_cast<LogoScene*>(scene)->animateLogo();
            break;
        case MAIN:
            dynamic_cast<MainScene*>(scene)->animateMain();
            break;
        case READY:
            dynamic_cast<ReadyScene*>(scene)->animateReady();
            break;
        case INGAME:
            dynamic_cast<IngameScene*>(scene)->animateIngame();
            break;
        case GAMEOVER: //이건 뭐지
           // dynamic_cast<GameoverScene*>(scene)->animateGameover();
            break;
        case CREDIT:
            dynamic_cast<CreditScene*>(scene)->animateCredit();
            break;
    }
}

void MainWindow::deleteOldScene()
{
    if(old_scene != NULL)
        delete old_scene;
}
