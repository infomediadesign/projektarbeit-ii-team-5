#pragma once
#include <vector>
#include "forestSpiritsStructs.h"

class Battle;

class BattleActor {
public:
    bool isPlayerControlled1() const;

    void setIsPlayerControlled(bool isPlayerControlled);

    bool isAlive1() const;

    void setIsAlive(bool isAlive);

    float getHp() const;

    void setHp(float hp);

    float getMana() const;

    void setMana(float mana);

    int getNat() const;

    void setNat(int nat);

    float getPat() const;

    void setPat(float pat);

    float getMat() const;

    void setMat(float mat);

    float getPdf() const;

    void setPdf(float pdf);

    float getMdf() const;

    void setMdf(float mdf);

    float getMaxHp() const;

    void setMaxHp(float maxHp);

    float getMaxMana() const;

    void setMaxMana(float maxMana);

    int getDNat() const;

    void setDNat(int dNat);

    std::vector<BattleActor*> *getOtherActors() const;

    void setOtherActors(std::vector<BattleActor*> *otherActors);

    int getNextAttack() const;

    void setNextAttack(battleAttackIndex nextAttack);

    bool isNeedAttackMenu() const;

    void setNeedAttackMenu(bool needAttackMenu);

    bool isPlayerControlled = false;
    bool isAlive = true;
    float hp = 100;
    float mana = 100;
    int nat = 10;
    float pat = 10;
    float mat = 10;
    float pdf = 10;
    float mdf = 10;
    float maxHP = 100;
    float maxMana = 100;
    float attackStr;
    int dNat = 10;
    Battle* myBattle;
    battleAttackIndex nextAttack = undefined;
    BattleActor* target = this;
    battleAttackIndex moveset[3] = {basic_attack,basic_attack,basic_attack};
public:
    BattleActor *getTarget() const;
    void autoTarget();
    void setTarget(BattleActor *target);

    bool needAttackMenu;


public:
    //getter
    BattleActor* getAddress();

    void startTurn();
    void evaluateAction();
    void executeAction();
    BattleActor(bool player, int archetype, Battle *theBattleImIn);

    void takeDamage(float damageBaseValue, float attackerStrength, int damageType);

    void die();

    void setNextAttackFromMoveset(int i);


};