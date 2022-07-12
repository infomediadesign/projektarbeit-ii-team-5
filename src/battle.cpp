
#include "battle.h"

void Battle::update(){
    if (!allActorsReadyForTurn()){
        playTurn();

    }
    else {
        for (const auto& it = theBattleActors.begin();it != theBattleActors.end();it++)
        this->isWaitingForPlayerInput = true;
        for (auto it = theBattleActors.begin():theBattleActors){
            if (it->getNextAttack() < 0)
        }
    }
}

void Battle::playTurn() {

}
