#pragma once

/*
 *400X180
 *65, 75
 *167 75
 *273 75
 */
class PausePopup : public QGameItem
{
    Q_OBJECT
public:
    CreditButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~CreditButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    ResumeButton    *resume;
    MenuButton      *menu;

};


class ResumeButton : public QGameItem
{
    Q_OBJECT
public:
    ResumeButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~ResumeButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class MenuButton : public QGameItem
{
    Q_OBJECT
public:
    MenuButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~MenuButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class ReloadButton : public QGameItem
{
    Q_OBJECT
public:
    ReloadButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~ReloadButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class BackButton : public QGameItem
{
    Q_OBJECT
public:
    BackButton(QGraphicsScene *scene, MainWindow *window);
    virtual ~BackButton();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
