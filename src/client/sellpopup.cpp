#include "sellpopup.h"
#include "ui_sellpopup.h"
#include "localgame.h"
#include <list>
#include <QString>

Sellpopup::Sellpopup(QWidget *parent, Player *player, int penalty) :
    QWidget(parent),
    ui(new Ui::Sellpopup),
    penalty(penalty)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);

    // initialize
    this->move(365, 152.5);
    this->player = player;
    needed_value = penalty - player->getEnergy();

    // setup blocks list that player owns
    std::list<Block*> block_list = player->getBlocks();
    block_num = block_list.size();
    blocks = new SubjectBlock*[block_num];
    checks = new QCheckBox*[block_num];

    int index = 0;
    for(std::list<Block*>::iterator itor = block_list.begin(); itor != block_list.end(); itor++) {
        blocks[index] = dynamic_cast<SubjectBlock*>(*itor);
        index++;
    }

    // list up checkbox elements
    for(int i=0; i < block_num; i++) {
        QString string = "";

        // append department
        string +=  convertDept(blocks[i]->getDept());

        string += " - ";

        // append Subject name
        string += blocks[i]->getName();

        string += " - ";

        // append grade
        string += convertGrade(blocks[i]->getGrade());

        string += " - ";

        // append sellprice
        string += QString::number(blocks[i]->getSellCost());
        
        QCheckBox* newCheck = new QCheckBox();
        newCheck->setText(string);

        checks[i] = newCheck;
        layout->addWidget(newCheck);

        connect(newCheck, SIGNAL(toggled(bool)), this, SLOT(calculate()));
    }


    // set labels
    ui->neededValue->setText(QString::number(needed_value));
    ui->selectedValue->setText("0");

    // connect
    connect(ui->sellButton, SIGNAL(clicked()), this, SLOT(sell()));
    connect(ui->bankruptButton, SIGNAL(clicked()), this, SLOT(bankrupt()));
}

Sellpopup::~Sellpopup()
{
    delete ui;
    delete layout;
    delete[] checks;
    delete[] blocks;
}


QString Sellpopup::convertDept(SubjectType::Type type)
{
    QString dept = "";

    switch(type) {
        using namespace SubjectType;
        case CSED:
            dept = QString::fromUtf8("컴공과");
            break;
        case ME:
            dept = QString::fromUtf8("기계공학과");
            break;
        case MATH:
            dept = QString::fromUtf8("수학과");
            break;
        case EE:
            dept = QString::fromUtf8("전자과");
            break;
        case PHYS:
            dept = QString::fromUtf8("물리과");
            break;
        case BIO:
            dept = QString::fromUtf8("수학과");
            break;
        case CHEM:
            dept = QString::fromUtf8("화학과");
            break;
        case IME:
            dept = QString::fromUtf8("산경과");
            break;
    }

    return dept;
}


QString Sellpopup::convertGrade(int grade)
{
    QString str = "";

    switch(grade) {
        case 2:
            str += "C";
            break;
        case 3:
            str += "B";
            break;
        case 4:
            str += "A";
            break;
    }  

    return str;
}


void Sellpopup::sell()
{
    qDebug() << "Selling Block!";
    int sellsum=0;
    // calculated selected value
    for(int i=0; i<block_num; i++) {
        if(checks[i]->isChecked()){
            sellsum += blocks[i]->getSellCost();
            player->removeBlock(blocks[i]);
        }
    }

    player->giveEnergy(sellsum - needed_value - penalty);
    SubjectBlock * cur_block = dynamic_cast<SubjectBlock*>(LocalGame::getInst()->getBoard()->getBlock(player->getPosition()));
    cur_block->getOwner()->giveEnergy(penalty);
    LocalGame::getInst()->turnOver();
    this->close();
}

void Sellpopup::bankrupt()
{
    qDebug() << "Player " << player->getId() << "bankrupted!";

    player->setBankrupt();
    LocalGame::getInst()->turnOver();
    this->close();
}

void Sellpopup::calculate()
{
    qDebug() << "Select";

    int selected = 0;

    // calculate selected
    for(int i=0; i<block_num; i++)
        if(checks[i]->isChecked())
            selected += blocks[i]->getSellCost();

    // update label
    ui->selectedValue->setText(QString::number(selected));

    // is enough?
    if(selected >= needed_value)
        ui->sellButton->setEnabled(true);
}
