
#include "BattleActor.h"

BattleActor *BattleActor::getAddress() {
    return this;
}

void BattleActor::startTurn()
{
    if (isPlayerControlled)
    {
        needAttackMenu = true;
    }
    else
    {
        nextAttack = evaluateAttack();
    }
}

int BattleActor::evaluateAttack(){
    return 0;
}