#include "sellpopup.h"
#include "ui_sellpopup.h"
#include <list>

Sellpopup::Sellpopup(QWidget *parent, Player *player, SubjectBlock *block) :
    QWidget(parent),
    ui(new Ui::Sellpopup)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);

    // initialize
    this->move(365, 152.5);
    this->player = player;
    needed_value = block->getPenaltyCost() - player->getEnergy();

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
            dept += "컴공과";
            break;
        case ME:
            dept += "기계과";
            break;
        case MATH:
            dept += "수학과";
            break;
        case EE:
            dept += "전자과";
            break;
        case PHYS:
            dept += "물리과";
            break;
        case BIO:
            dept += "생명과";
            break;
        case CHEM:
            dept += "화학과";
            break;
        case IME:
            dept += "산경과";
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

    player->giveEnergy(sellsum - needed_value);

    this->close();
}

void Sellpopup::bankrupt()
{
    qDebug() << "Player " << player->getId() << "bankrupted!";

    player->setBankrupt();
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
