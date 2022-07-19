
#include "battle.h"

void Battle::frameRoutine() {
    switch(battleState){
        case startOfTick:
            break;
        case playerActionSelect:
            break;
        case actorsActionSelection:
            if (currentlyActingNumber >= theBattleActors .size()){
                this->battleState = playOutRound;
                currentlyActingNumber = 0;
            }
            else {
                if (theBattleActors[currentlyActingNumber].getNextAttack() == -1) {
                    if (theBattleActors[currentlyActingNumber].isPlayerControlled1()) {
                        this->battleState = playerActionSelect;
                    } else {
                        theBattleActors[currentlyActingNumber].evaluateAttack();
                        currentlyActingNumber++;
                    }
                }
            }
            break;
        case textBubble:
            break;
        case winningScreen:
            break;
        case playOutRound:
            break;
        case playingAnimation:
            break;
    }
};