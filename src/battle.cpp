
#include "battle.h"

void Battle::frameRoutine() {
    switch(battleState){
        case startOfTick:
            decreaseAllNats();
            break;
        case playerActionSelect:
            break;
        case actorsActionSelection:
            if (currentlyActingNumber >= theBattleActors .size()){ //checks if the round is done
                this->battleState = playOutRound;
                currentlyActingNumber = 0;
            }
            else {
                if (theBattleActors[currentlyActingNumber].getNat() <= 0) { //checks if the currently looked at actor is eligible to act this turn
                    if (theBattleActors[currentlyActingNumber].isPlayerControlled1()) {
                        this->battleState = playerActionSelect;
                    } else {
                        theBattleActors[currentlyActingNumber].evaluateAction();
                        currentlyActingNumber++;
                    }
                }
            }
            break;
        case textBubble:
            if (controlInputs->confirm){
                this->infoText = "";
                this->battleState = playOutRound;
            }
            //TODO
            break;
        case winningScreen:
            if (controlInputs->confirm == 1){
                this->killMe = true;
            }

            //TODO
            break;
        case playOutRound:
            if (theBattleActors[currentlyActingNumber].getNat()<= 0){
                theBattleActors[currentlyActingNumber].executeAction();
            }
            else
            //TODO
            break;
        case playingAnimation:
            //TODO
            break;
    }
}

void Battle::decreaseAllNats() {
    for (auto & i : theBattleActors){
        i.setNat(i.getNat() - 1);
    }
}