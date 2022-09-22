
#include <iostream>
#include "BattleActor.h"
#include "math.h"
#include "battle.h"

BattleActor *BattleActor::getAddress() {
    return this;
}

BattleActor::BattleActor(bool player, int archetype, Battle *theBattleImIn) {
    this->isPlayerControlled = player;
    this->myBattle = theBattleImIn;
    switch (archetype) {
        case 0: //Blaize
            std::cout << "init blaize\n";
            this->maxHP = 500;
            this->hp = 500;
            this->pat = 40;
            this->pdf = 40;
            this->dNat = 7;
            this->nat = 7;
            this->attackStr = 50;
            this->moveset[1] = foxFire;
            this->moveset[2] = foxShield;
            break;
        case 1: //EVERYBODY WANTS TO BE, MY ENEMY!
            std::cout << "init enemy\n";
            this->maxHP = 300;
            this->hp = 300;
            this->pat = 50;
            this->pdf = 60;
            this->dNat = 9;
            this->nat = 3;
            this->attackStr = 35;
            this->moveset[1] = shroomAngerment;
            this->moveset[2] = basic_attack;
            break;
        default:;
    }
    return;

}

void BattleActor::evaluateAction() {
    nextAttack = moveset[GetRandomValue(0, 2)];
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


int BattleActor::getNextAttack() const {
    return nextAttack;
}

void BattleActor::setNextAttack(battleAttackIndex nextAttack) {
    this->nextAttack = nextAttack;
}

bool BattleActor::isNeedAttackMenu() const {
    return needAttackMenu;
}

void BattleActor::setNeedAttackMenu(bool needAttackMenu) {
    this->needAttackMenu = needAttackMenu;
}

void BattleActor::executeAction() {
    switch (this->nextAttack) {
        case basic_attack:
            target->takeDamage(this->attackStr, this->pat, 0);
            this->nat = this->dNat;
            this->nextAttack = undefined;
            break;
        default:;
    }
}

BattleActor *BattleActor::getTarget() const {
    return target;
}

void BattleActor::setTarget(BattleActor *target) {
    BattleActor::target = target;
}

void BattleActor::autoTarget() {
    for (auto it = 0; it != myBattle->theBattleActors.size(); it++) {
        if (!this->isPlayerControlled) {
            if (myBattle->theBattleActors[it]->isPlayerControlled) {
                this->target = myBattle->theBattleActors[it];
            }
        } else {
            if (!myBattle->theBattleActors[it]->isPlayerControlled) {
                this->target = myBattle->theBattleActors[it];
            }
        }
    }
}

void BattleActor::takeDamage(float damageBaseValue, float attackerStrength, int damageType) {


    this->hp -=
            damageBaseValue * pow(attackerStrength / (damageType ? this->mdf : this->pdf), 1 / global_damageCalcConstB);

    if (this->hp <= 0) {
        die();
    }
}

void BattleActor::die() {
    this->hp = 0;
    this->isAlive = false;
}

void BattleActor::setNextAttackFromMoveset(int i) {
    this->nextAttack = this->moveset[i];
}
