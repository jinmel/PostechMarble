#pragma once
#include "mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPixmap>
#include <QEasingCurve>

class QGameItem :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public slots:
    void animationFinished();
    void hideFinished();
public:
    QGameItem(QGraphicsScene* scene, MainWindow *window);
    QGameItem(QGameItem * parent=0);
    virtual ~QGameItem();
    QPixmap* image();
    void setImage(const char * filename);
    void setParent(QGameItem *parent);
    void rotateImage(qreal angle);
    //Game object animation
    void animateTo(qreal x,qreal y,int duration,
                 const QEasingCurve & curve=QEasingCurve::Linear);
    void animateBy(qreal x,qreal y,int duration,
                   const QEasingCurve & curve=QEasingCurve::Linear);
    void hide(bool fade,int duration=1000);
    void show(bool fade,int duration=1000);
    MainWindow* getWindow();

private:
    QGameItem(); //disabled to explicitly expcify the parent scene of the item
    QTimeLine *timer;
    QPixmap *item_image;
    QGraphicsItemAnimation *animation;
protected:
    MainWindow *window;
    QGraphicsScene * parent_scene;
};
