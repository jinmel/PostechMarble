#include "sellpopup.h"
#include "ui_sellpopup.h"
#include <list>

Sellpopup::Sellpopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sellpopup)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);

    /*
    Player* player = new Player(new QGameItem(), 1);

    std::list<Block*> block_list = player->getBlocks();
    block_num = block_list.size();
    blocks = new SubjectBlock*[block_num];
    checks = new QCheckBox*[block_num];

    int index = 0;
    for(std::list<Block*>::iterator itor = block_list.begin(); itor != block_list.end(); itor++) {
        blocks[index] = (SubjectBlock*)*itor;
        index++;
    }

    for(int i=0; i < block_num; i++) {
        QString string = "Test";

        // append department
        string +=  convertDept(blocks[i]->getDept());

        string += " - ";

        // append Subject name
        string += blocks[i]->getName();

        string += " - ";

        // append grade
        string += convertGrade(blocks[i]->getGrade());
        
        QCheckBox* newCheck = new QCheckBox();
        newCheck->setText(string);

        checks[i] = newCheck;
        layout->addWidget(newCheck);
    }
    */

    // for test use
    block_num = 10;

    for(int i=0; i < 10; i++) {
        QString string = "Test";


        QCheckBox* newCheck = new QCheckBox();
        newCheck->setText(string);

        checks[i] = newCheck;
        layout->addWidget(newCheck);
    }
    // test end

    // connect
    connect(ui->sellButton, SIGNAL(clicked()), this, SLOT(sell()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->bankruptButton, SIGNAL(clicked()), this, SLOT(bankrupt()));


}

Sellpopup::~Sellpopup()
{
    delete ui;
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

    /*
    for(int i=0; i<block_num; i++) {
        if(checks[i]->isChecked())
            player->sellBlock(blocks[i]);
    }
    */
    this->close();
}

void Sellpopup::bankrupt()
{
    //qDebug() << "Player " << player->getId() << "bankrupted!";

    //player->setBankrupt();
    this->close();
}
