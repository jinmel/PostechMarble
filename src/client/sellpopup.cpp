#include "sellpopup.h"
#include "ui_sellpopup.h"

Sellpopup::Sellpopup(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::sellpopup)
{
    ui->setupUi(this);
    layout = ui->verticalLayout;

    Block** blocks = player->getBlocks();

    for(int i=0; i < blocks->size(); i++);
}

Sellpopup::~Sellpopup()
{
    delete ui;
}

