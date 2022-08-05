
#include <iostream>
#include "battle.h"

const bool debug = true;

void Battle::frameRoutine() {
    switch(battleState){
        case startOfTick:
            if (debug)
                std::cout << "DEBUG: Tick is started\n";
            decreaseAllNats();
            this->battleState = playerActionSelect;
            break;
        case playerActionSelect:
            if (debug)
                std::cout << "DEBUG: Player Action selection\n";
            if (controlInputs->up >= 1){
                theBattleActors[currentlyActingNumber]->setNextAttack(1);
                theBattleActors[currentlyActingNumber]->autoTarget();
                this->currentlyActingNumber++;
                this->battleState = actorsActionSelection;
            }

            break;
        case actorsActionSelection:
            if (debug)
                std::cout << "DEBUG: Actors Action confirmation\n";
            if (currentlyActingNumber >= theBattleActors.size()){ //checks if the round is done
                this->battleState = playOutRound;
                currentlyActingNumber = 0;
            }
            else {
                if (theBattleActors[currentlyActingNumber]->getNat() <= 0) { //checks if the currently looked at actor is eligible to act this turn
                    if (theBattleActors[currentlyActingNumber]->isPlayerControlled1()) {
                        this->battleState = playerActionSelect;
                    } else {
                        theBattleActors[currentlyActingNumber]->evaluateAction();
                        currentlyActingNumber++;
                    }
                }
                else{
                    currentlyActingNumber++;
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
            if (debug)
                std::cout << "DEBUG: Round is being played\n";
            if (theBattleActors[currentlyActingNumber]->getNat()<= 0){
                theBattleActors[currentlyActingNumber]->executeAction();
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
        i->setNat(i->getNat() - 1);
    }
}

void Battle::initTestBattle() {

    this->theBattleActors.push_back(new BattleActor(true,0,&this->theBattleActors));
    this->theBattleActors.push_back(new BattleActor(false,1,&this->theBattleActors));
}

Battle::Battle(int advantage, int encounternumber){
    ;
}
