#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QTimeLine>


class CustomItem : public QGraphicsPixmapItem
{
private:
    QApplication *app;

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        qDebug() << "Custom item clicked.";
        QGraphicsItemAnimation * animation = new QGraphicsItemAnimation();
        animation->setItem(this);

        QTimeLine * timer = new QTimeLine(50000);
        animation->setTimeLine(timer);

        for(int i =0 ; i < 200; i ++){
            animation->setPosAt(1/200.0,QPointF(this->x()+ i,this->y()));
        }
        timer->start();

//        app->quit();
//        QGraphicsItem::mousePressEvent(event);
    }

    void setApplication(QApplication* app)
    {
        this->app = app;
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logo = new QGraphicsScene(this);
    ui->graphicsView->setScene(logo);
    logo->setSceneRect(0, 0, 1280, 720);

    // Set Background
    QGraphicsPixmapItem *background = logo->addPixmap(QPixmap(":images/back_dummy.png"));
    background->setPos(0, 0);

    CustomItem *ok_test = new CustomItem();
    ok_test->setPixmap(QPixmap(":/images/button_ok.png"));
    ok_test->setPos(620, 550);
    ok_test->setApplication(app);
    logo->addItem(ok_test);


    QGraphicsPixmapItem *image = logo->addPixmap(QPixmap(":images/hammer.png"));
    image->setPos(1.0, 1.0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setApplication(QApplication* app)
{
    this->app = app;
}
