
#include "BattleActor.h"

BattleActor *BattleActor::getAddress() {
    return this;
}

BattleActor::BattleActor(bool player, int archetype, std::vector<BattleActor*>* others) {
    this->isPlayerControlled = player;
    this->otherActors = others;
    switch (archetype){
        case (0): //Blaize
        this->maxHP = 500;
        this->hp = 500;
        this->pat = 40;
        this->pdf = 40;
        this->dNat = 7;
        this->nat = 7;
        this->attackStr = 50;
        break;
        case (1): //EVERYBODY WANTS TO BE, MY ENEMY!
        this->maxHP = 300;
        this->hp = 300;
        this->pat = 50;
        this->pdf = 60;
        this->dNat = 9;
        this->nat = 3;
    }

}

int BattleActor::evaluateAction(){
    return 0;
}

bool BattleActor::isPlayerControlled1() const {
    return isPlayerControlled;
}

void BattleActor::setIsPlayerControlled(bool isPlayerControlled) {
    BattleActor::isPlayerControlled = isPlayerControlled;
}

bool BattleActor::isAlive1() const {
    return isAlive;
}

void BattleActor::setIsAlive(bool isAlive) {
    BattleActor::isAlive = isAlive;
}

float BattleActor::getHp() const {
    return hp;
}

void BattleActor::setHp(float hp) {
    BattleActor::hp = hp;
}

float BattleActor::getMana() const {
    return mana;
}

void BattleActor::setMana(float mana) {
    BattleActor::mana = mana;
}

int BattleActor::getNat() const {
    return nat;
}

void BattleActor::setNat(int nat) {
    BattleActor::nat = nat;
}

float BattleActor::getPat() const {
    return pat;
}

void BattleActor::setPat(float pat) {
    BattleActor::pat = pat;
}

float BattleActor::getMat() const {
    return mat;
}

void BattleActor::setMat(float mat) {
    BattleActor::mat = mat;
}

float BattleActor::getPdf() const {
    return pdf;
}

void BattleActor::setPdf(float pdf) {
    BattleActor::pdf = pdf;
}

float BattleActor::getMdf() const {
    return mdf;
}

void BattleActor::setMdf(float mdf) {
    BattleActor::mdf = mdf;
}

float BattleActor::getMaxHp() const {
    return maxHP;
}

void BattleActor::setMaxHp(float maxHp) {
    maxHP = maxHp;
}

float BattleActor::getMaxMana() const {
    return maxMana;
}

void BattleActor::setMaxMana(float maxMana) {
    BattleActor::maxMana = maxMana;
}

int BattleActor::getDNat() const {
    return dNat;
}

void BattleActor::setDNat(int dNat) {
    BattleActor::dNat = dNat;
}

std::vector<BattleActor*> *BattleActor::getOtherActors() const {
    return otherActors;
}

void BattleActor::setOtherActors(std::vector<BattleActor*> *otherActors) {
    this->otherActors = otherActors;
}

int BattleActor::getNextAttack() const {
    return nextAttack;
}

void BattleActor::setNextAttack(int nextAttack) {
    this->nextAttack = nextAttack;
}

bool BattleActor::isNeedAttackMenu() const {
    return needAttackMenu;
}

void BattleActor::setNeedAttackMenu(bool needAttackMenu) {
    this->needAttackMenu = needAttackMenu;
}

void BattleActor::executeAction() {
    //TODO
}

BattleActor *BattleActor::getTarget() const {
    return target;
}

void BattleActor::setTarget(BattleActor *target) {
    BattleActor::target = target;
}

void BattleActor::autoTarget(){
    for (auto it = otherActors->begin();it!=otherActors->end();it++)
    {
        if((*it)->isPlayerControlled1()){
            this->target = *it;
        }
    }
}
