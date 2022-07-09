#pragma once
#include <vector>


class BattleActor {
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
    int dNat = 10;
    std::vector<BattleActor>* otherActors;
    int nextAttack = -1;
    bool needAttackMenu;
public:

private:

public:
    BattleActor(std::vector<BattleActor>* otherActors, int actorType);
    //getter
    BattleActor* getAddress();

    void startTurn();
    int evaluateAttack();
};