#pragma once
#include <QGraphicsScene>
#include "../mainwindow.h"
#include "../qgameitem.h"

class CreditScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void switchToMain();
private:
    MainWindow* window;
    QGameItem* credit;

    void setupCredit();
    void animateCredit();

public:
    CreditScene(qreal x=0, qreal y=0, qreal width=1280,
                qreal height=720,
                QObject* parent=0);
    ~CreditScene();
};
