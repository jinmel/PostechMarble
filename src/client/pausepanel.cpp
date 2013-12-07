#include "pausepanel.h"
#include "localgame.h"


/*
 *400X180
 *65, 75
 *167 75
 *273 75
 *340 0(Close)
 */

PausePanel::PausePanel(QGraphicsScene *scene, MainWindow *window)
    : QGameItem(scene, window)
{
    this->setImage(":images/ingame/pause/pause_panel.png");

    resume = new ResumeButton(this);
    resume->setPos(65, 75);

    reload = new ReloadButton(this);
    reload->setPos(167, 75);

    menu = new MenuButton(this);
    menu->setPos(273, 75);
}

PausePanel::~PausePanel()
{
    delete resume;
    delete reload;
    delete menu;
}

ResumeButton::ResumeButton(QGameItem *parent)
    : QGameItem(parent)
{
    this->setImage(":images/ingame/pause/resume.png");
}


ResumeButton::~ResumeButton()
{

}

void ResumeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Resume button clicked.";
    setImage(":images/ingame/pause/resume_pressed.png");
}

void ResumeButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/ingame/pause/resume.png");

    dynamic_cast<PausePanel*>(this->parent())->hide(false);
}

void ResumeButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/ingame/pause/resume.png");
}


// MenuButton
MenuButton::MenuButton(QGameItem *parent)
    : QGameItem(parent)
{
    this->setImage(":images/ingame/pause/menu.png");
}


MenuButton::~MenuButton()
{

}

void MenuButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Menu button clicked.";
    setImage(":images/ingame/pause/menu_pressed.png");
}

void MenuButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/ingame/pause/menu.png");
    window->switchScene(SceneType::MAIN);
}

void MenuButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/ingame/pause/menu.png");
}

// ReloadButton
ReloadButton::ReloadButton(QGameItem *parent)
    : QGameItem(parent)
{
    this->setImage(":images/ingame/pause/reload.png");
}


ReloadButton::~ReloadButton()
{

}

void ReloadButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Reload button clicked.";
    setImage(":images/ingame/pause/reload_pressed.png");
}

void ReloadButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/ingame/pause/reload.png");
    window->switchScene(SceneType::READY);
}

void ReloadButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/ingame/pause/reload.png");
}


// PauseButton
PauseButton::PauseButton(QGraphicsScene *scene, MainWindow *window, PausePanel *panel)
    : QGameItem(scene, window)
{
    this->panel = panel;
    this->setImage(":images/ingame/pause/pause.png");
}


PauseButton::~PauseButton()
{

}

void PauseButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Pause button clicked.";
    setImage(":images/ingame/pause/pause_pressed.png");
    panel->show(false);
}

void PauseButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setImage(":images/ingame/pause/pause.png");
}

void PauseButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // ignore input in this case
    setImage(":images/ingame/pause/pause.png");
}
