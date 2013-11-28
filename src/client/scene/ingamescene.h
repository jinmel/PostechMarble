#ifndef INGAMESCENE_H
#define INGAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>

class IngameScene : public QGraphicsScene
{
private:
    QGraphicsPixmapItem *background;

public:
    IngameScene(qreal x=0,qreal y=0,qreal width=1280,
                qreal height=1280,
                QObject * parent=0);
    QGraphicsPixmapItem* setBackgroundPixmap(const char * filename);
    QGraphicsPixmapItem* backgroundPixmap();
};

#endif // INGAMESCENE_H
