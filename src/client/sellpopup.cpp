#include "sellpopup.h"
#include "ui_sellpopup.h"

sellpopup::sellpopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sellpopup)
{
    ui->setupUi(this);
}

sellpopup::~sellpopup()
{
    delete ui;
}
