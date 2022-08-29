
#include <iostream>
#include "battle.h"

// constructor
Battle::Battle(int advantage, int encounternumber)
{
    this->background = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Background.png");
    this->baseActors = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Actors_Base.png");
    this->baseAttacks = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Attacks_Base.png");
    this->baseItems = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Items_Base.png");
}

// GUI Stuff
void Battle::update_gui()
{
    // down
    if (IsKeyPressed(KEY_S) && gui_currentBox < 3)
    {
        gui_currentBox++;
    }
    else if (IsKeyPressed(KEY_W) && gui_currentBox > 1)
    {
        gui_currentBox--;
    }
}

void Battle::draw()
{
    drawGUIBox(this->background);

    switch (gui_currentBox)
    {
        case 1:
            drawGUIBox(this->baseActors);
            break;

        case 2:
            drawGUIBox(this->baseAttacks);
            break;

        case 3:
            drawGUIBox(this->baseItems);
            break;
    }
}

void Battle::drawGUIBox(Texture2D currentTexture)
{
    DrawTexturePro(currentTexture,
                   {0, 0, (float)currentTexture.width, (float)currentTexture.height},
                   {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   {0, 0}, 0, WHITE);
}

// Battle Stuff
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

