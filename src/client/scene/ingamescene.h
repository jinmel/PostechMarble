#ifndef INGAMESCENE_H
#define INGAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QTimeLine>
#include "../dice.h"
#include "../qgameitem.h"
#include "../board.h"
#include "../player.h"

//주사위 클래스의 그래픽
class DiceGraphicItem;
//주사위 표시기
class DiceValuePanel;
//캐릭터 상태창
class CharacterStatusBar;

class IngameScene : public QGraphicsScene
{
private:
    MainWindow * const window; //cannot be changed
    QGraphicsPixmapItem *background;
    DiceGraphicItem *dice_graphic;
    DiceValuePanel *first_dice_panel;
    DiceValuePanel *second_dice_panel;
    Board *board;
    QGameItem *status1;
    QGameItem *status2;

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
    QTimeLine * timeline;
    DiceValuePanel();
public slots:
    void endSpin();
    void setValue(int value);
    void spinValue(int frame);
signals:
    void diceDetermined(int value,bool is_double);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


#endif // INGAMESCENE_H
