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
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public slots:
    void animationFinished();
    void hideFinished();
public:
    QGameItem(QGraphicsScene* scene);
    QPixmap* image();
    void setImage(char * filename);
    //Game object animation
    void animate(qreal x,qreal y,int duration,
                 const QEasingCurve & curve=QEasingCurve::Linear);
    void hide(bool fade,int duration=1000);
    void show(bool fase,int duration=1000);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QGameItem(); //disabled to explicitly expcify the parent scene of the item
    QGraphicsScene * parent_scene;
    QTimeLine *timer;
    QPixmap *item_image;
    QGraphicsItemAnimation *animation;
};

#endif // QGAMEITEM_H
