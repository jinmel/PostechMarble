#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include "qgameitem.h"

class CustomItem : public QGraphicsPixmapItem
{
private:
    QApplication *app;
    MainWindow *window;
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        qDebug() << "Custom item clicked.";
        setPixmap(QPixmap(":images/button_ok_click.png"));

        window->switchToMain();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        setPixmap(QPixmap(":images/button_ok.png"));
    }

    void setApplication(QApplication* app)
    {
        this->app = app;
    }

    void setMainWindow(MainWindow *window)
    {
        this->window = window;
    }
};

void MainWindow::switchScene(int scenetype){

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScenes();
    ui->graphicsView->setScene(logo);
    animateLogo();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setApplication(QApplication* app)
{
    this->app = app;
}


void MainWindow::setupScenes()
{
    logo = new QGraphicsScene(0, 0, 1280, 720, this);
    menu = new QGraphicsScene(0, 0, 1280, 720, this);
    ready = new QGraphicsScene(0, 0, 1280, 720, this);
    ingame = new QGraphicsScene(0, 0, 1280, 720, this);

    // setup for logo
    QGraphicsPixmapItem *back_logo = logo->addPixmap(QPixmap(":images/logo/logo_background.png"));
    back_logo->setPos(0, 0);

    QGameItem *ok_test = new QGameItem(logo, this);
    ok_test->setPixmap(QPixmap(":/images/button_ok.png"));
    ok_test->setPos(600, 550);

    QGraphicsPixmapItem *team_logo = logo->addPixmap(QPixmap(":images/logo/team_logo.png")); //900 170
    team_logo->setPos(190, 275);


    // setup for main
    QGraphicsPixmapItem *back_main = menu->addPixmap(QPixmap(":images/main/main_background.png"));
    back_main->setPos(0, 0);

    QGameItem *start_button = new QGameItem(menu, this);
    start_button->setImage(":/images/button_ok.png");
    start_button->setPos(600,400);

    QGameItem *credit_button = new QGameItem(menu, this);
    credit_button->setImage(":/images/button_ok.png");
    credit_button->setPos(600,500);

    // setup for ready
    QGraphicsPixmapItem *ready_logo = logo->addPixmap(QPixmap(":images/logo/logo_background.png"));
    ready_logo->setPos(0, 0);
}

void MainWindow::animateLogo()
{
    QGraphicsItem* team_logo = logo->items().value(0);

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

    QMediaPlayer* sound = new QMediaPlayer();
    sound->setMedia(QUrl::fromLocalFile("D:/Development/C&C++/CSED232 Project/src/client/sound/logo_dang.mp3"));
    sound->setVolume(80);

    animation->start();
    sound->play();
}


void MainWindow::switchToMain()
{
    // implement this with smoother transition
    ui->graphicsView->setScene(menu);
}

