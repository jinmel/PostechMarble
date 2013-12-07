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
#include <QMap>
#include "dice.h"
#define NUMBER_OF_BLOCKS 32
#define NEXT_POS(current_pos) ((current_pos + 1) % 32)

using namespace std;

Player::Player(QGameItem* parent,int _id) : QGameItem(parent)
{
    Dice::getInst();
    //randomly determine CharacterType
    switch(rand() % 5){
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
            break;
    }

    id = _id;
    name = "";
    position = 0;

    energy = 500;
    if(character_type == CharacterType::GENIUS)
        energy += 100;

    bankrupt = false;
    mobile = true;
    immobile_penalty = 0;
    plural = false;

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
        color = QString("red");
        break;
    case 2:
        color = QString("blue");
        break;
    case 3:
        color = QString("green");
        break;
    case 4:
        color = QString("yellow");
        break;
    }

    using namespace BlockCoords;

    for(int i =0; i < 32; i ++){
        player_coord[i] = block_coord[i];
    }

    for(int i=1; i< 24; i ++){
        player_coord[i] += QPointF(0,-40);
    }

    for(int i=17; i<24; i++){
        player_coord[i] += QPointF(40,0);
    }

    player_coord[8] = block_coord[8];

    setPos(player_coord[0]);

    // step sound load
    mediaplayer = new QMediaPlayer();
    mediaplayer->setMedia(QUrl::fromLocalFile(QFileInfo("sound/piece_move.wav").absoluteFilePath()));
    mediaplayer->setVolume(100);

    // end initialize
    qDebug() << "Player Created" << endl;
}

Player::~Player()
{

    qDebug() << "Player Destroyed" << endl;
}

void Player::setColor(QString color_str){
    color = color_str;
}

QString Player::getColor(){
    return color;
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

    for(list<Block*>::iterator itor = own_blocks.begin(); itor != own_blocks.end(); itor++)
       removeBlock(dynamic_cast<SubjectBlock*>(*itor));
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
    sleep->setStartValue(player_coord[current_pos]);
    sleep->setEndValue(player_coord[current_pos]);
    seq_animation_group->addAnimation(sleep);

    while(steps){
        next_pos = NEXT_POS(current_pos);
        QPropertyAnimation * step_animation
                = new QPropertyAnimation(this,"pos");        
        step_animation->setDuration(step_interval);
        step_animation->setStartValue(player_coord[current_pos]);
        step_animation->setEndValue(player_coord[next_pos]);
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
    QPointF target = player_coord[block_num];
    QPropertyAnimation * step_animation
            = new QPropertyAnimation(this,"pos");
    step_animation->setDuration(2000);
    step_animation->setStartValue(player_coord[getPosition()]);
    step_animation->setEndValue(target);
    step_animation->setEasingCurve(QEasingCurve::InOutQuint);
    step_animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(step_animation,SIGNAL(finished()),this,SLOT(arrived()));
    position = block_num;
}

void Player::stepForward(){
    position = NEXT_POS(position);
    mediaplayer->play();
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
    sblock->setOwner(NULL);
    registered.find(((SubjectBlock*)block)->getDept())->second--;
    own_blocks.remove(block);
}

void Player::giveSalary()
{
    qDebug() << "Player " << id << " received salary";
    //maybe add animation for gaining energy

    QMediaPlayer* mediaplayer = new QMediaPlayer();
    mediaplayer->setMedia(QUrl::fromLocalFile(QFileInfo("sound/coinsprinkle.mp3").absoluteFilePath()));
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
    int majored_b = 0;

    QMap<SubjectType::Type, int> B_grades;

    using namespace SubjectType;
    B_grades[BIO] = 0;
    B_grades[CHEM] = 0;
    B_grades[CSED] = 0;
    B_grades[EE] = 0;
    B_grades[MATH] = 0;
    B_grades[ME] = 0;
    B_grades[IME] = 0;
    B_grades[PHYS] = 0;

    Block* block;
    foreach(block,own_blocks){
        SubjectBlock* sblock = dynamic_cast<SubjectBlock*>(block);
        if(sblock->getGrade() == SubjectBlock::B ||
                sblock->getGrade() == SubjectBlock::A)
            B_grades[sblock->getDept()]++;
    }

    for(map<SubjectType::Type, int>::iterator i=registered.begin(); i != registered.end(); i++) {
        if(i->second == 3)
            majored ++;
    }

    for(QMap<SubjectType::Type, int>::iterator i=B_grades.begin(); i != B_grades.end(); i++) {
        if(i.value() == 3)
            majored_b ++;
    }

    if(plural && majored ==2)
        return true;
    else if(!plural && majored_b == 1)
        return true;
    else
        return false;

}

void Player::payEnergy(int payenergy)
{
    if(energy >= payenergy)
    {
        QMediaPlayer* coinsound = new QMediaPlayer();
        coinsound->setMedia(QUrl::fromLocalFile(QFileInfo("sound/coinspread.mp3").absoluteFilePath()));
        coinsound->setVolume(100);
        coinsound->play();
        energy-=payenergy;
    }
    else{
        if(getAssetValue() >= payenergy){
            Sellpopup * popup = new Sellpopup(QGameItem::getWindow(), this, payenergy);
            popup->show();
        }
        else
            setBankrupt();
    }
    emit energyChanged(this->energy);
}

void Player::giveEnergy(int paidenergy){
    energy+=paidenergy;
    QMediaPlayer* coinsound = new QMediaPlayer();
    coinsound->setMedia(QUrl::fromLocalFile(QFileInfo("sound/coinspread.mp3").absoluteFilePath()));
    coinsound->setVolume(100);
    coinsound->play();
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

    if(id == 1 || id ==3)
        filename += QString("io_");
    else if(id == 2 || id ==4)
        filename += QString("id_");

    filename += color + QString("_");

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
