#include "ingamescene.h"
#include <QPixmap>

IngameScene::IngameScene(qreal x, qreal y,
                         qreal width, qreal height,
                         QObject *parent)
    : QGraphicsScene(x,y,width,height,parent)
{

}

QGraphicsPixmapItem* IngameScene::setBackgroundPixmap(const char * filename){
    return this->addPixmap(QPixmap(filename));
}

QGraphicsPixmapItem* IngameScene::backgroundPixmap(){
    return background;

}
