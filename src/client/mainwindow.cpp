#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QDebug>

class CustomItem : public QGraphicsPixmapItem
{
private:
    QApplication *app;

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        qDebug() << "Custom item clicked.";
        app->quit();
        QGraphicsItem::mousePressEvent(event);
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
    QGraphicsPixmapItem *background = logo->addPixmap(QPixmap(":/back_dummy.png"));
    background->setPos(0, 0);

    CustomItem *ok_test = new CustomItem();
    ok_test->setPixmap(QPixmap(":/button_ok.png"));
    ok_test->setPos(620, 550);
    ok_test->setApplication(app);
    logo->addItem(ok_test);

    //QGraphicsPixmapItem *ok_button = logo->addPixmap(QPixmap(":/button_ok.png"));
    //ok_button->setPos(620, 550);

    QGraphicsPixmapItem *image = logo->addPixmap(QPixmap(":/hammer.png"));
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
