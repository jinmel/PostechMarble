#pragma once
#include "pausepanel.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QTimeLine>
#include <QWidget>
#include <QLayout>
#include <QMediaPlayer>
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
//포토제닉
class PhotoGenicItem;
//캐릭터 상태 표시
class PlayerStatusDisplay;

namespace Ui{
class PhotoGenicPopup;
}

class IngameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    MainWindow * const window; //cannot be changed
    QGraphicsPixmapItem *background;
    DiceGraphicItem *dice_graphic;
    DiceValuePanel *first_dice_panel;
    DiceValuePanel *second_dice_panel;
    QGameItem *double_graphic;
    Board *board;
    QTimeLine *double_timeline;
    PlayerStatusDisplay *status1;
    PlayerStatusDisplay *status2;
    QMediaPlayer *bgm_player;
    PausePanel *pause_panel;
    PauseButton *pause_button;

    QGameItem *winner_image;//image of winner character

public:
    IngameScene(qreal x=0,qreal y=0,qreal width=1280,
                qreal height=720,
                QObject * parent=0);
    virtual ~IngameScene();
    QGraphicsPixmapItem* setBackgroundPixmap(const char * filename);
    QGraphicsPixmapItem* backgroundPixmap();
    void animateIngame();

private slots:
    void showDouble();
    void hideDouble();
public slots:
    void switchtoGameover();
};

class DiceGraphicItem: public QGameItem
{
    Q_OBJECT

public:
    DiceGraphicItem(QGraphicsScene * scene, MainWindow * window);
private:
    DiceGraphicItem();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class DiceValuePanel : public QGameItem
{
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


class PhotoGenicItem : public QGameItem {
    Q_OBJECT
public:
    PhotoGenicItem(QGraphicsScene * scene, MainWindow * window);
    ~PhotoGenicItem();
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
public slots:
    void slideFinish();
    void showPhotos();

    void slidePhoto(int frame);
private:
    //Ui::PhotoGenicPopup *ui;
    //QVBoxLayout *layout;
    QTimeLine * timeline;


signals:
protected:
};

class PlayerStatusDisplay : public QGameItem{
    Q_OBJECT
public:
    PlayerStatusDisplay(QGameItem * parent,Player * player);
    ~PlayerStatusDisplay();
public slots:
    void setEnergyText(int energy);
    void spinNumber(int frame);
    void endSpin();
    void activate();
    void disable();
private:
    QTimeLine * m_timeline;
    int m_last_energy;
    int m_display_energy;
    Player const * const m_player;
    QGraphicsTextItem * m_energy_label;
};


