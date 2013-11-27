#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

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
    void animateLogo();
    void switchToMain();

private:
    Ui::MainWindow *ui;
    QApplication *app;
    QGraphicsView *viewWindow;
    QGraphicsScene *logo;
    QGraphicsScene *menu;
    QGraphicsScene *ready;
    QGraphicsScene *ingame;

    void setupScenes();
};
