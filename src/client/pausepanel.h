#pragma once
#pragma once
#include <QGraphicsScene>
#include "mainwindow.h"
#include "qgameitem.h"

class ResumeButton;
class MenuButton;
class ReloadButton;

class PausePanel : public QGameItem
{
    Q_OBJECT
public:
    PausePanel(QGraphicsScene *scene, MainWindow *window);
    virtual ~PausePanel();

private:
    ResumeButton    *resume;
    MenuButton      *menu;
    ReloadButton    *reload;
};


class ResumeButton : public QGameItem
{
    Q_OBJECT
public:
    ResumeButton(QGameItem *parent);
    virtual ~ResumeButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class MenuButton : public QGameItem
{
    Q_OBJECT
public:
    MenuButton(QGameItem *parent);
    virtual ~MenuButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class ReloadButton : public QGameItem
{
    Q_OBJECT
public:
    ReloadButton(QGameItem *parent);
    virtual ~ReloadButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class PauseButton : public QGameItem
{
    Q_OBJECT
public:
    PauseButton(QGraphicsScene *scene, MainWindow *window, PausePanel *panel);
    virtual ~PauseButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    PausePanel *panel;
};
