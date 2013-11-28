#ifndef QGAMEITEM_H
#define QGAMEITEM_H

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
public slots:
    void animationFinished();
    void hideFinished();
public:
    QGameItem(QGraphicsScene* parent);
    QPixmap* image();
    void setImage(char * filename);
    //Game object animation
    void animate(qreal x,qreal y,int duration,
                 const QEasingCurve & curve=QEasingCurve::InOutElastic);
    void hide(bool fade=false,int duration=1000);
    void show(bool fase=false,int duration=1000);

private:
    QGameItem(); //disabled to explicitly expcify the parent scene of the item
    QGraphicsScene * parent_scene;
    QTimeLine *timer;
    QPixmap *item_image;
    QGraphicsItemAnimation *animation;
};

#endif // QGAMEITEM_H
