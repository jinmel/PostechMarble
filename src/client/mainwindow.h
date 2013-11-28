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
    void switchScene(int scenetype);
private:
    Ui::MainWindow *ui;
    QApplication *app;
    QGraphicsView *viewWindow;
    QGraphicsScene *logo;
    QGraphicsScene *menu;
    QGraphicsScene *ready;
    QGraphicsScene *ingame;
    QGraphicsScene *credit;

    void setupScenes();
};
