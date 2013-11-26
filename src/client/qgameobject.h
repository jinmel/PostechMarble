#ifndef QGAMEOBJECT_H
#define QGAMEOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItemAnimation>


class QGameObject : public QGraphicsPixmapItem
{
private:
public:
    QGameObject(QPixmap & pmap);
    QGameObject();


};

#endif // QGAMEOBJECT_H
