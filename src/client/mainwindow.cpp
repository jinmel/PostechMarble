#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logo = new QGraphicsScene(this);
    ui->graphicsView->setScene(logo);
    logo->setSceneRect(0, 0, 1280, 720);

    QGraphicsPixmapItem *image = logo->addPixmap(QPixmap(":/hammer.png"));
    image->setPos(1.0, 1.0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
