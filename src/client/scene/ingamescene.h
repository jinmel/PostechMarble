#ifndef INGAMESCENE_H
#define INGAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include "../dice.h"
#include "../qgameitem.h"

class DiceGraphicItem;
class DiceValuePanel;

class IngameScene : public QGraphicsScene
{
private:
    QGraphicsPixmapItem *background;
    DiceGraphicItem *dice_graphic;
    DiceValuePanel *first_panel;
    DiceValuePanel *second_panel;
public:
    IngameScene(qreal x=0,qreal y=0,qreal width=1280,
                qreal height=720,
                QObject * parent=0);
    virtual ~IngameScene();
    QGraphicsPixmapItem* setBackgroundPixmap(const char * filename);
    QGraphicsPixmapItem* backgroundPixmap();
};

class DiceGraphicItem: public QGameItem {
    Q_OBJECT
signals:
    void firstValueChanged(int value);
    void secondValueChanged(int value);
public:
    DiceGraphicItem(QGraphicsScene * scene, MainWindow * window);
private:
    DiceGraphicItem();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class DiceValuePanel : public QGameItem {
    Q_OBJECT
public:
    DiceValuePanel(QGraphicsScene * scene,MainWindow * window);
private:
    int diceValue;
    DiceValuePanel();
public slots:
    void setValue(int value);
};

#endif // INGAMESCENE_H
