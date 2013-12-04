#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "types.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setApplication(QApplication* app);
    void animateScene(int scenetype);

public slots:
    void switchScene(int scenetype);

private:
    Ui::MainWindow *ui;
    QApplication *app;
    QGraphicsView *viewWindow;
    QGraphicsScene *scene;
};
