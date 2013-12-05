#include "player.h"
#include "subjectblock.h"
#include "types.h"
#include <iostream>
#include <algorithm>
#include <QDebug>
#include "board.h"
#include <QtGlobal>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "localgame.h"
#include "sellpopup.h"
#include <QMediaPlayer>
#include <QFileInfo>
#include <QDir>
#define NUMBER_OF_BLOCKS 32
#define NEXT_POS(current_pos) ((current_pos + 1) % 32)

using namespace std;

Player::Player(QGameItem* parent,int _id) : QGameItem(parent)
{
    //randomly determine CharacterType
    int n = rand() % 5;
    switch(n){
    case 0:
        character_type = CharacterType::LOL;
        break;
    case 1:
        character_type = CharacterType::GENIUS;
        break;
    case 2:
        character_type = CharacterType::HARD_WORKER;
        break;
    case 3:
        character_type = CharacterType::OUTSIDER;
        break;
    case 4:
        character_type = CharacterType::ALCOHOLIC;
    }

    id = _id;
    name = "";
    position = 0;

    energy = 1000;
    if(character_type == CharacterType::GENIUS)
        energy += 200;

    bankrupt = false;
    mobile = true;
    immobile_penalty = 0;
    plural = false;

    character_type = CharacterType::NONE;
    //totalownsubjectenergy=0;//지우고 동적으로 계산하라

    //initialize map
    using namespace SubjectType;
    registered[BIO] = 0;
    registered[CHEM] = 0;
    registered[CSED] = 0;
    registered[EE] = 0;
    registered[MATH] = 0;
    registered[ME] = 0;
    registered[IME] = 0;
    registered[PHYS] = 0;

    switch(_id){
    case 1:
        player_color = QString("red");
        break;
    case 2:
        player_color = QString("blue");
        break;
    }

    // end initialize
    qDebug() << "Player Created" << endl;
}

Player::~Player()
{
    //delete own_blocks;

    qDebug() << "Player Destroyed" << endl;
}


// Accessor Methods
int Player::getPosition() const
{
    return position;
}

QPointF Player::adjustCoord(QPointF &coord){
    return coord;
}


bool Player::isBankrupt() const
{
    return bankrupt;
}


bool Player::isMobile() const
{
    return mobile;
}


int Player::getEnergy() const
{
    return energy;
}


int Player::getPenalty() const
{
    return immobile_penalty;
}

bool Player::isPlural() const
{
    return plural;
}


CharacterType::Type Player::getType() const
{
    return character_type;
}


list<Block*> Player::getBlocks() const
{
    return own_blocks;
}

// Methods
void Player::setEnergy(int energy)
{
    this->energy = energy;
    emit energyChanged(this->energy);
}

void Player::setPlural(bool plural)
{
    this->plural = plural;
}


void Player::setBankrupt()
{
    setEnergy(0);
    bankrupt = true;
}

// set player to stay mouindo
// parm: how long to stay in mouindo
void Player::setMouindo(int penalty)
{
    this->immobile_penalty = penalty;
    mobile = false;
}

void Player::setMobile(bool mobile){
    this->mobile = mobile;
    immobile_penalty = 0;
}

void Player::escapeAttempt(){
    immobile_penalty--;
    if(immobile_penalty==0)
        mobile = true;
}

//probably unused forever...
bool Player::escapeMouindo()
{
    if(mobile)
        return true;

    else {

        if(immobile_penalty == 0) {
            mobile = true;
            return true;
        }

        else {
            // roll a dice
            immobile_penalty--;
            return false;
        }
    }
}


void Player::walkBy(int steps)
{
    using namespace BlockCoords;
    LocalGame::getInst()->setGameState(LocalGameState::PLAYER_MOVING);
    const int step_interval = 300; //0.1 seconds
    int current_pos = position;
    int next_pos;

    QSequentialAnimationGroup * seq_animation_group
            = new QSequentialAnimationGroup;

    //add sleep animation
    QPropertyAnimation * sleep
            = new QPropertyAnimation(this,"pos");
    sleep->setDuration(1800);
    //don't move
    sleep->setStartValue(block_coord[current_pos]);
    sleep->setEndValue(block_coord[current_pos]);
    seq_animation_group->addAnimation(sleep);

    while(steps){
        next_pos = NEXT_POS(current_pos);
        QPropertyAnimation * step_animation
                = new QPropertyAnimation(this,"pos");        
        step_animation->setDuration(step_interval);
        step_animation->setStartValue(block_coord[current_pos]);
        step_animation->setEndValue(block_coord[next_pos]);
        step_animation->setEasingCurve(QEasingCurve::InOutQuint);
        connect(step_animation,SIGNAL(finished()),this,SLOT(stepForward()));
        seq_animation_group->addAnimation(step_animation);
        steps--; //decrease one step
        current_pos = next_pos;

    }
    seq_animation_group->start(QAbstractAnimation::DeleteWhenStopped);

    connect(seq_animation_group,SIGNAL(finished()),this,SLOT(arrived()));
    //position = current_pos;
}

void Player::jumpTo(int block_num){
    using namespace BlockCoords;
    LocalGame::getInst()->setGameState(LocalGameState::PLAYER_MOVING);
    QPointF target = block_coord[block_num];
    QPropertyAnimation * step_animation
            = new QPropertyAnimation(this,"pos");
    step_animation->setDuration(2000);
    step_animation->setStartValue(block_coord[getPosition()]);
    step_animation->setEndValue(target);
    step_animation->setEasingCurve(QEasingCurve::InOutQuint);
    step_animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(step_animation,SIGNAL(finished()),this,SLOT(arrived()));
    position = block_num;
}

void Player::stepForward(){
    position = NEXT_POS(position);
    if(position == 0){
        giveSalary();
    }
}

void Player::arrived(){
    qDebug() << "arrived at:"<<position;
    emit playerArrived(this);
}

bool Player::hasBlock(Block* block)
{
    // subject block check
    if(block->getType() != BlockType::SUBJECT) {
        qDebug() << "This is not a Subject Block!";
        return false;
    }

    list<Block*>::iterator finder = own_blocks.end();
    finder = find(own_blocks.begin(), own_blocks.end(), block);

    // no matching
    if(finder == own_blocks.end())
        return false;
    else
        return true;
}

void Player::addBlock(Block *block)
{
    SubjectBlock * subj_block = dynamic_cast<SubjectBlock*>(block);
    subj_block->setOwner(this);
    registered.find(((SubjectBlock*)block)->getDept())->second++;
    own_blocks.push_back(block);
}


void Player::removeBlock(Block *block)
{
    if(!hasBlock(block)) {
        qDebug() << "You don't have that block. Check Again!";
        return;
    }
    SubjectBlock * sblock = dynamic_cast<SubjectBlock*>(block);
    sblock->setGrade(SubjectBlock::NONE);
    registered.find(((SubjectBlock*)block)->getDept())->second--;
    own_blocks.remove(block);
}

void Player::giveSalary()
{
    qDebug() << "Player " << id << " received salary";
    //maybe add animation for gaining energy

    QMediaPlayer* mediaplayer = new QMediaPlayer();
    mediaplayer->setMedia(QUrl::fromLocalFile(QFileInfo("sound/coin.wav").absoluteFilePath()));
    mediaplayer->setVolume(100);
    mediaplayer->play();

    if(character_type == CharacterType::HARD_WORKER)
        energy += 150;
    else
        energy += 100;

    emit energyChanged(this->energy);
}


bool Player::checkWinStatus()
{
    int majored = 0;

    for(map<SubjectType::Type, int>::iterator i = registered.begin(); i != registered.end(); i++) {
        if(i->second == 3)
            majored ++;
    }

    if(plural && majored >= 2)
        return true;
    else if (!plural && majored >= 1)
        return true;
    else
        return false;
}

void Player::payEnergy(int payenergy)
{
    if(energy >= payenergy)
        energy-=payenergy;
    else{
        if(getAssetValue() >= payenergy){
            Sellpopup * popup = new Sellpopup;
            popup->show();
        }
        else
            setBankrupt();
    }
    emit energyChanged(this->energy);
}
void Player::giveEnergy(int paidenergy){
    energy+=paidenergy;
    emit energyChanged(this->energy);
}

int Player::getId() const {
    return id;
}

void Player::setType(CharacterType::Type type) {
    character_type = type;
}

int Player::getAssetValue() {

    int asset = 0;

    if(own_blocks.empty()) {
        qDebug() << "Player has nothing!";
        asset = 0;
    }
    else {
        for(list<Block*>::iterator itor = own_blocks.begin(); itor != own_blocks.end(); itor++) {
           asset += dynamic_cast<SubjectBlock*>(*itor)->getSellCost();
        }
    }
    return asset;
}

void Player::animatePlayerImage(int frame){
    QString filename = QString(":/images/ingame/character/");

    int zone = position /8 ;

    if(zone == 0){
        filename += QString("top_up_");
    }
    else if(zone ==1){
        filename += QString("top_right_");
    }
    else if(zone ==2){
        filename += QString("top_down_");
    }
    else {
        filename += QString("top_right_");
    }

    if(id == 1)
        filename += QString("io_");
    else if(id == 2)
        filename += QString("id_");

    filename += player_color + QString("_");

    LocalGame * game_inst = LocalGame::getInst();

    if(game_inst->getGameState() == LocalGameState::PLAYER_MOVING
            && game_inst->getCurrentPlayer() == this)
        filename += QString("walk_");
    else
        filename += QString("stand_");

    filename += QString::number(frame).rightJustified(3,'0') + QString(".png");

    //qDebug() << filename;

    QImage image(filename);

    QTransform rotate;
    rotate.rotate(180);

    if(zone == 3)
        image = image.mirrored(true,false);

    setPixmap(QPixmap::fromImage(image));
}
