#include "qgameitem.h"
#include <QString>
#include <QDebug>
#include <QLine>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>


QGameItem::QGameItem()
{
   //void constructor never called
}


QGameItem::~QGameItem()
{

}

QGameItem::QGameItem(QGraphicsScene *scene, MainWindow *window)
    : QObject(scene)
{
    parent_scene = scene;
    parent_scene->addItem(this);
    timer = NULL;
    animation = NULL;
    item_image = NULL;
    this->window = window;
}

QGameItem::QGameItem(QGameItem *parent)
    : QGraphicsPixmapItem(parent) , QObject(parent)
{
    parent_scene = parent->scene();
    timer = NULL;
    animation = NULL;
    item_image = NULL;
    window = parent->getWindow();
}

MainWindow* QGameItem::getWindow(){
    return this->window;
}

QPixmap * QGameItem::image(){
    return this->item_image;
}

void QGameItem::setImage(const char * filename){
    if(item_image == NULL){
        item_image = new QPixmap(QString(filename));
        setPixmap(*item_image);
    }
    else{
        QPixmap * del = item_image;
        item_image = new QPixmap(QString(filename));
        setPixmap(*item_image);
        delete del;
    }
}

void QGameItem::animateTo(qreal dest_x,qreal dest_y,int duration,
                        const QEasingCurve & curve){
    // Start animate this class
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");
    // 2 second duration animation
    anim->setDuration(duration);
    // position to start animation
    anim->setStartValue(this->pos());
    // end position of animation
    anim->setEndValue(QPointF(dest_x,dest_y));
    // easing curve
    anim->setEasingCurve(curve);
    // Listen animation finished signal
    QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));
    // Start animation and delete QPropertyAnimation class on the end
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
void QGameItem::animateBy(qreal delta_x,qreal delta_y,int duration,
                        const QEasingCurve & curve){
    // Start animate this class
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");
    // 2 second duration animation
    anim->setDuration(duration);
    // position to start animation
    anim->setStartValue(this->pos());
    // end position of animation
    anim->setEndValue(this->pos() + QPointF(delta_x,delta_y));
    // easing curve
    anim->setEasingCurve(curve);
    // Listen animation finished signal
    QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));
    // Start animation and delete QPropertyAnimation class on the end
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

//duration in ms
void QGameItem::hide(bool fade,int duration){
    if(!fade)
        QGraphicsPixmapItem::hide();
    else {
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
        opacityEffect->setOpacity(1.0);
        this->setGraphicsEffect(opacityEffect);

        QPropertyAnimation * animation = new QPropertyAnimation();
        animation->setTargetObject(opacityEffect);
        animation->setPropertyName("opacity");
        animation->setDuration(duration);
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);
        animation->setEasingCurve(QEasingCurve::Linear);

        QObject::connect(animation,SIGNAL(finished()),this,SLOT(hideFinished()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

//duration in ms
void QGameItem::show(bool fade,int duration){
    if(!fade){
        QGraphicsPixmapItem::show();
    }
    else{
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
        opacityEffect->setOpacity(0.0);
        this->setGraphicsEffect(opacityEffect);

        QPropertyAnimation * animation = new QPropertyAnimation();
        animation->setTargetObject(opacityEffect);
        animation->setPropertyName("opacity");
        animation->setDuration(duration);
        animation->setStartValue(0.0);
        animation->setEndValue(1.0);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void QGameItem::animationFinished(){
    qDebug() << "Animation fininshed";
}

void QGameItem::hideFinished(){
    this->hide(false);
}
