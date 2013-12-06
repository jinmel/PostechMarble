#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimeLine>
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
    void animateScene(int scenetype);

private:
    Ui::MainWindow *ui;
    QApplication *app;
    QGraphicsView *viewWindow;
    QGraphicsScene *scene;
    QGraphicsScene *old_scene;
    QTimeLine *delete_delay;

private slots:
    void deleteOldScene();
};
