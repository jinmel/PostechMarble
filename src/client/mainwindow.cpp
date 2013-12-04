#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgameitem.h"
#include "scene/creditscene.h"
#include "scene/logoscene.h"
#include "scene/mainscene.h"
#include "scene/ingamescene.h"
#include "scene/readyscene.h"
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
    switchScene(SceneType::LOGO);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

// Methods
// Utility Functions
void MainWindow::switchScene(int scenetype)
{
    QGraphicsScene *new_scene;

    using namespace SceneType;
    switch(scenetype) {
        case LOGO:
            new_scene = new LogoScene(0, 0, 1280, 720, this);
            break;
        case MAIN:
            new_scene = new MainScene(0, 0, 1280, 720, this);
            break;
        case READY:
            new_scene = new ReadyScene(0, 0, 1280, 720, this);
            break;
        case INGAME:
            new_scene = new IngameScene(0,0,1280,720,this);
            break;
        case CREDIT:
            new_scene = new CreditScene(0,0,1280,720,this);
            break;
    }

    ui->graphicsView->setScene(new_scene);

    if(scene != NULL)
        delete scene;
    scene = new_scene;

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
        case CREDIT:
            dynamic_cast<CreditScene*>(scene)->animateCredit();
            break;
    }
}
