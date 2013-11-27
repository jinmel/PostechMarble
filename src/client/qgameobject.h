#pragma once

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
