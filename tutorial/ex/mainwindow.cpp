#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    object_state = 1;
    image = new QImage("/Users/crank/Code/csed232Project/tutorial/ex/gogo.jpg");
    if(image->isNull()){
        QMessageBox msgbox;
        msgbox.setText("fail to load image");
        msgbox.exec();
    }

    brush = new QBrush();
    brush->setTextureImage(*image);
    ui->graphicsView->setForegroundBrush(*brush);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (object_state == 1)
        ui->graphicsView->move(0, 100);
    if (object_state == 2)
        ui->graphicsView->move(400,100);
    if (object_state == 3)
        ui->graphicsView->move(400,0);
    if (object_state == 4){
        ui->graphicsView->move(0,0);
        object_state = 0;
    }
    object_state ++;

}
