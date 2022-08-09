#pragma once
#include <vector>


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

    void setNextAttack(int nextAttack);

    bool isNeedAttackMenu() const;

    void setNeedAttackMenu(bool needAttackMenu);

private:
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
    std::vector<BattleActor*>* otherActors;
    int nextAttack = -1;
    BattleActor* target;
public:
    BattleActor *getTarget() const;
    void autoTarget();
    void setTarget(BattleActor *target);

private:
    bool needAttackMenu;

private:

public:
    BattleActor(std::vector<BattleActor>* otherActors, int actorType);
    //getter
    BattleActor* getAddress();

    void startTurn();
    int evaluateAction();
    void executeAction();
    BattleActor(bool player, int archetype,std::vector<BattleActor*>* others);
};