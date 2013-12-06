#include "qgameitem.h"
#include <QString>
#include <QDebug>
#include <QLine>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTransform>

/*
                                           MMMM
                                       MMMMMMMMMM
                                     MMMMMMMMMMMMMM
         MMMM                        MMMMMMMMMMMMMMM
      MMMMMMMMMM                    MMMMMMMMMMMMMMMM
     MMMMMMMMMMMM                  MMMMMMMMMMMMMMMMMM
   MMMMMMMMMMMMMMM                 MMMMMMMMMMMMMMMMMM
  MMMMMMMMMMMMMMMMM                MMMMMMMMMMMMMMMMMM
  MMMMMMMMMMMMMMMMM                MMMMMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMM               MMMMMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMM               MMMMMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMM                MMMMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMM     MMMMMMM    MMMMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMM MMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMM  MMMMMMMMM----MMMMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMM MMMMMMMMMM------MMMMMMMMMMMMMM
 MMMMMMMMMMMMMMMMMMMMM----MMM---/=\--MMMMMMMMMMMM
  MMMMMMMMMMMMMMMMMMM--==--MM------\--MMM MMMMMM
  MMMMMMMMMMMMMMMMMM--/-----M-------\--MMM
   MMMMMMMMMMMMMMMM--/-----------------MMM
     MMMMMMMMM  MMM--|------------------MMM
       MMMMM   MMM------/..\---/..\-----MMM
               MMM-----/....\-/....\----MMMM
              MMMM-----......-......----MMMM
              MMMM-----......-......----MMMM
              MMMM-----......-.MM...---MMMMM
              MMMMM----...MM.-.MMM..---MMMMM
              MMMMM----..MMM.-\MMM./---MMMMM
              MMMMMM---\.MMM.--\M./---/-----
              MMMMMM----\\M/=======\---------
              MM----M--/====-MMMMM------------
                -----------MMMMMMMM-----------
               ------------MMMMMMMM-----------
               ------------MMMMMMMM----X------
               ------_/----MMMMMMM-----/-\----
               -----/\------MMMMM------|-----
               ----/--\---------------/-----
                -------\-------------M-----
                --------=-----------MM----
                  -------\=========MMM---
                   ------MMMMMMMMMMMM---
                     -----MXXXXXXXXM---
                    MMMMM--XXXXXXXX--
                 MMMMMMMMM---XXXX---M
            MMMMMMMMMMMMMMM--------MMM
           MMMMMM:++MMMMMMMMM----MMMMM
          MMMMMM:MMMMMMMMMMMMMMMMMMMMMM
          MMMMM:M////MMMMMMMMMMMMMMMMMM
          MMMMM//////////MMMMMMMMMMMMMMM
          MMMM/////////////MMMMMMMMMMMMM
          MMM///////////////MMMMMMMMMMMM
           M///...////////////MMMMMMMMMMM
           ///....////..///////MMMMMMMMMM
           ///....///....///////MM  MMMMMM
           ///....///....////////M  MMMMMM
          ////...///.....///////// MMMMMMMM
          ////..////...../////////MMMMMMMMM
          //////////...../////////MMMMMMMMM
          //////////....//////////MMMMMMMM
          ///////////..///////////MMMMMMM
          ////////////////////////MMMMM
          ////////////////////////MMM
           ///////////////////////
           ///////////////////////
           ///////////////////////
           ///////////////////////
          ////////////////////////
          ////////////////////////
          //////X//////////////////
           //////XXX///////////////
             ///////V//////////////
                /////X//////////:::
                 MMMM/////MMMM::MM
                  MMMMM|MMMMMMM   MMM
                  MMMMMM|MMMMMM      MMMM____
                   MMMMM|MMMMMM              \------
                    MMMM\MMMMMM                     -_
                     MMMM|MMMMMM                      \
                     MMMM\MMMMMM                       \
                      MMMM\MMMMM                        |
                       MMM|MMMMMM                      /
        VVVVVVV      VVMMMM\MMMMM                     /
     VVVVVVVVVXVVVV  VVVMMMM|MMMM                   _-
     VVVVVVVVVVXVVVVVIVVVMMIIMMMMVV            -----
    VVVVVVVVVVVVVXXVVVIVVVVIIMMMMMVV
    VVVVVVVVVVVVVVVXXVVVVVVVIIVMMMVVVVVVV
    VVVVVVVVVVVVVVVVXVXVVVVVIIVVVVVVVVVVVVVVVV
    VVVVVVVVVVVVVVVVVXVXVVVVIVIVVVVVVVVVVVVXVVVVVV
    VVVVVVVVVVVVVVVVVVXVXVVIVVVIVVVVVVVVVXVVXVVVVVVV
     VVVVVVVVVVVVVVVVVVXVXVIVVVVVVVVVVVVXVVXVVVVVVVVV
     VVVVVVVVVVVVVVVVVVVXVVIVVVVVVVVVVVXVXVVVVVVVVVVVV
      VVVVVVVVVVVVVVVVVVVVVVIVVVVVVVVVXVXVVVVVVVVVVVVV
       VVVVVVVVVVVVVVVVVVVVVIVVVVVVVVXVXVVVVVVVVVVVVVV
         VVVVVVVVVVVVVVVVVV  VVVVVVVXXVVVVVVVVVVVVVVVV
           VVVVVVVVVVVVVV     VVVXXXVVVVVVVVVVVVVVVVVV
              VVVVVVVVV        VXVVVVVVVVVVVVVVVVVVVV
                                 VVVVVVVVVVVVVVVVVVV
                                  VVVVVVVVVVVVVVVVV
                                   VVVVVVVVVVVVVV
                                     VVVVVVVVV
The most important class written by Jin Suk Park ME 20110307
 */

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
    scene->addItem(this);
    timer = NULL;
    animation = NULL;
    item_image = NULL;
    this->window = window;
}


QGameItem::QGameItem(QGameItem *parent)
    : QObject(parent) ,QGraphicsPixmapItem(parent)
{
    timer = NULL;
    animation = NULL;
    item_image = NULL;
    if(parent != NULL)
        setParent(parent);
}

MainWindow* QGameItem::getWindow(){
    return this->window;
}

void QGameItem::setParent(QGameItem *parent){
    QObject::setParent(parent);
    QGraphicsPixmapItem::setParentItem(parent);
    window = parent->getWindow();
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
        connect(animation,SIGNAL(finished()),this,SLOT(hideFinished()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

//duration in ms
void QGameItem::show(bool fade,int duration){
    if(!fade){
        QGraphicsPixmapItem::show();
    }
    else{
        QGraphicsPixmapItem::show();
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

void QGameItem::rotateImage(qreal angle){
    //check if item_image is initialized
    if(!item_image)
        return;
    QTransform rotation;
    rotation.rotate(angle);
    QPixmap * rotated_pixmap = new QPixmap(item_image->transformed(rotation));
    setPixmap(*rotated_pixmap);
    delete item_image;
    item_image = rotated_pixmap;
}

void QGameItem::animationFinished(){
    qDebug() << "Animation fininshed";
}

void QGameItem::hideFinished(){
    this->hide(false);
}
