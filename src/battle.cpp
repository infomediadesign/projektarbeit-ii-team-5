
#include <iostream>
#include "battle.h"

// constructor
Battle::Battle(int advantage, int encounternumber) {
    this->background = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Background.png");
    this->baseActors = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Actors_Base.png");
    this->baseAttacks = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Attacks_Base.png");
    this->baseItems = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Items_Base.png");

    this->infoActions = LoadTexture("assets/graphics/UI/Fightscreen/Info_Actions.png");
    this->infoItems = LoadTexture("assets/graphics/UI/Fightscreen/Info_Items.png");

    this->marker_1 = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Box_1_Marker.png");
    this->marker_2 = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Box_2_Marker.png");
    this->markerItems = LoadTexture("assets/graphics/UI/Fightscreen/Fightscreen_Box_Items_Marker.png");

    this->player = LoadTexture("assets/graphics/Sprites/Character/Player/Blaize_Idle.png");
    this->shroom = LoadTexture("assets/graphics/Sprites/Character/Enemy/Shroom_Idle.png");

    gui_setSlots();
}

// GUI Stuff
void Battle::update_gui() {
    // down
    if (!isActionSelectVisible && !isItemSelectVisible) {
        if (IsKeyPressed(KEY_S) && gui_currentScreen < 2) {
            gui_currentScreen++;
        } else if (IsKeyPressed(KEY_W) && gui_currentScreen > 0) {
            gui_currentScreen--;
        }

    }

    if (IsKeyPressed(KEY_E)) {
        switch (gui_currentScreen) {
            // you cant enter the case 0 and do something with actors

            case 1:
                isActionSelectVisible = true;
                isItemSelectVisible = false;
                break;

            case 2:
                isActionSelectVisible = false;
                isItemSelectVisible = true;
                break;

        }
    } else if (IsKeyPressed(KEY_Q) && showActionInfo == false && showItemInfo == false) {
        isActionSelectVisible = false;
        isItemSelectVisible = false;

        gui_currentAction = 0;
        this->gui_currentItem = 0;
    }


    if (isActionSelectVisible) {
        if (IsKeyPressed(KEY_D) && gui_currentAction < 4) {
            gui_currentAction++;
        } else if (IsKeyPressed(KEY_A) && gui_currentAction > 0) {
            gui_currentAction--;
        } else if (gui_currentAction == 4 && IsKeyPressed(KEY_E)) {
            this->showActionInfo = true;
        }

        if (IsKeyPressed(KEY_Q)) {
            this->showActionInfo = false;
        }
    }

    if (isItemSelectVisible) {
        if (IsKeyPressed(KEY_D) && gui_currentItem < 3) {
            gui_currentItem++;
        } else if (IsKeyPressed(KEY_A) && gui_currentItem > 0) {
            gui_currentItem--;
        } else if (gui_currentItem == 3 && IsKeyPressed(KEY_E)) {
            this->showItemInfo = true;
        }

        if (IsKeyPressed(KEY_Q)) {
            this->showItemInfo = false;
        }
    }


    onButtonPress();

}

void Battle::draw() {
    ClearBackground(BROWN);

    drawGUIBox(background);

    drawBattlePlayer(player, {100, 450});
    drawBattleEnemy(shroom, {900, 450});

    switch (gui_currentScreen) {
        case 0:
            drawGUIBox(this->baseActors);
            break;

        case 1:
            drawGUIBox(this->baseAttacks);
            break;

        case 2:
            drawGUIBox(this->baseItems);
            break;
    }

    if (isActionSelectVisible) {
        drawGUISelection(this->marker_2, boxActionsPositions[gui_currentAction]);
    } else if (isItemSelectVisible && gui_currentItem <= 2) {
        drawGUISelection(this->markerItems, boxItemsPosition[gui_currentItem]);
    } else if (isItemSelectVisible && gui_currentItem == 3) {
        drawGUISelection(this->marker_2, boxActionsPositions[4]);
    } else {
        drawGUISelection(this->marker_1, box1Positions[gui_currentScreen]);
    }


    if (showActionInfo == true) {
        DrawTexturePro(this->infoActions,
                       {0, 0, (float) this->infoActions.width, (float) this->infoActions.height},
                       {this->boxInfoPosition},
                       {0, 0}, 0, WHITE);
    } else if (showItemInfo == true) {
        DrawTexturePro(this->infoItems,
                       {0, 0, (float) this->infoItems.width, (float) this->infoItems.height},
                       {this->boxInfoPosition},
                       {0, 0}, 0, WHITE);
    }

}

void Battle::drawGUIBox(Texture2D currentTexture) {
    DrawTexturePro(currentTexture,
                   {0, 0, (float) currentTexture.width, (float) currentTexture.height},
                   {(float) GetScreenWidth() / 2 - ((float) currentTexture.width * gui_scaleFactor) / 2,
                    (float) GetScreenHeight() / 2 - ((float) currentTexture.height * gui_scaleFactor) / 2,
                    (float) currentTexture.width * gui_scaleFactor, (float) currentTexture.height * gui_scaleFactor},
                   {0, 0}, 0, WHITE);
}

void Battle::drawGUISelection(Texture2D currentTexture, Vector2 position) {
    DrawTexturePro(currentTexture,
                   {0, 0, (float) currentTexture.width, (float) currentTexture.height},
                   {position.x, position.y, (float) currentTexture.width * gui_scaleFactor,
                    (float) currentTexture.height * gui_scaleFactor},
                   {0, 0}, 0, WHITE);
}

void Battle::drawBattlePlayer(Texture2D texture, Vector2 position) {
    // with every loop set actor frames + 1
    this->actor_frames++;

    // frame offset is calculated by current frames of actor and frame speed as well as width of texture
    // so it will switch every few frames to a new frame on the spritesheet
    this->actor_frame_offset = (actor_frames / 40) % 2;

    DrawTexturePro(texture,
                   {(float) actor_frame_offset * 64, 0, 64, 32},
                   {position.x, position.y, (float) 64 * 7, (float) 32 * 7},
                   {16 * 4, 16 * 4}, 0, WHITE);
}

void Battle::drawBattleEnemy(Texture2D texture, Vector2 position) {
    this->actor_frames++;

    this->actor_frame_offset = (actor_frames / 60) % 2;

    DrawTexturePro(texture,
                   {(float) actor_frame_offset * 32, 0, 32, 32},
                   {position.x, position.y, 32 * 7, 32 * 7},
                   {16 * 4, 16 * 4}, 0, WHITE);
}

void Battle::resetGUI() {
    gui_currentScreen = 0;
    gui_currentItem = 0;
    gui_currentAction = 0;
    gui_currentBox = 0;

    isItemSelectVisible = false;
    isActionSelectVisible = false;
}

void Battle::gui_setSlots() {
    // Party - Actions - Items
    this->box1Positions[0] = {(float) 9 * gui_scaleFactor, (float) GetScreenHeight() - (50 * gui_scaleFactor)};
    this->box1Positions[1] = {(float) box1Positions[0].x, (float) box1Positions[0].y + 13 * gui_scaleFactor};
    this->box1Positions[2] = {(float) box1Positions[1].x, (float) box1Positions[1].y + 13 * gui_scaleFactor};

    // Attack 1-3 - Wait - Infos
    this->boxActionsPositions[0] = {(float) 61 * gui_scaleFactor, (float) GetScreenHeight() - (40 * gui_scaleFactor)};
    this->boxActionsPositions[1] = {(float) boxActionsPositions[0].x + 35 * gui_scaleFactor,
                                    (float) boxActionsPositions[0].y};
    this->boxActionsPositions[2] = {(float) boxActionsPositions[1].x + 35 * gui_scaleFactor,
                                    (float) boxActionsPositions[1].y};
    this->boxActionsPositions[3] = {(float) boxActionsPositions[2].x + 35 * gui_scaleFactor,
                                    (float) boxActionsPositions[2].y};
    this->boxActionsPositions[4] = {(float) boxActionsPositions[3].x + 47 * gui_scaleFactor,
                                    (float) boxActionsPositions[3].y - 2 * gui_scaleFactor};

    // Items 1-3 - Infos
    this->boxItemsPosition[0] = {(float) 80 * gui_scaleFactor, (float) GetScreenHeight() - 41 * gui_scaleFactor};
    this->boxItemsPosition[1] = {(float) boxItemsPosition[0].x + 41 * gui_scaleFactor, boxItemsPosition[0].y};
    this->boxItemsPosition[2] = {(float) boxItemsPosition[1].x + 38 * gui_scaleFactor, boxItemsPosition[0].y};
    this->boxItemsPosition[3] = {(float) boxActionsPositions[3].x + 43 * gui_scaleFactor,
                                 (float) boxActionsPositions[3].y - 2 * gui_scaleFactor};

    this->boxInfoPosition = {(float) GetScreenWidth() / 2 - infoActions.width / 2 * gui_scaleFactor,
                             (float) GetScreenHeight() / 2 - (infoActions.height / 2) * gui_scaleFactor,
                             (float) this->infoActions.width * gui_scaleFactor,
                             (float) this->infoActions.height * gui_scaleFactor};

}


//--------------------------------------------------------------------------------------------------------------------//
// Battle Stuff
const bool debug = true;

void Battle::frameRoutine() {
    switch (battleState) {
        case startOfTick:
            if (debug) {
                std::cout << "DEBUG: Tick is started\n";
            }
            currentTurn++;
            std::cout
                    << TextFormat("It is tick %i. Blaize's HP are %f and the angry shrooms is %f\n", this->currentTurn,
                                  this->theBattleActors[0]->getHp(), this->theBattleActors[1]->getHp());
            decreaseAllNats();
            this->battleState = playerActionSelect;
            break;
        case playerActionSelect:
            if (debug && IsKeyPressed(KEY_H))
                std::cout << "DEBUG: Player Action selection\n";

            break;
        case actorsActionSelection:
            actorsActionSelectionRoutine();
            break;
        case textBubble:
            if (controlInputs->confirm) {
                this->infoText = "";
                this->battleState = playOutRound;
            }
            //TODO
            break;
        case winningScreen:
            if (controlInputs->confirm == 1) {
                this->killMe = true;
            }

            //TODO
            break;
        case playOutRound:
            if (debug)
                std::cout << "DEBUG: Round is being played\n";
            if (theBattleActors[currentlyActingNumber]->getNat() <= 0) {
                theBattleActors[currentlyActingNumber]->executeAction();
            }
            currentlyActingNumber++;

            if (currentlyActingNumber >= theBattleActors.size()) {
                currentlyActingNumber = 0;
                this->battleState = startOfTick;
            }
            break;
        case playingAnimation:
            //TODO
            break;
    }
}

void Battle::actorsActionSelectionRoutine() {
    if (debug)
        std::cout << "DEBUG: Actors Action confirmation\n";
    if (currentlyActingNumber > theBattleActors.size()) { //checks if the round is done
        this->battleState = playOutRound;
        currentlyActingNumber = 0;
    } else {
        if (theBattleActors[currentlyActingNumber]->getNat() <=
            0) { //checks if the currently looked at actor is eligible to act this turn
            if (theBattleActors[currentlyActingNumber]->isPlayerControlled1()) {
                this->battleState = playerActionSelect;
            } else {
                theBattleActors[currentlyActingNumber]->evaluateAction();
                currentlyActingNumber++;
            }
        } else {
            currentlyActingNumber++;
        }
    }
}

void Battle::decreaseAllNats() {
    for (auto &i: theBattleActors) {
        i->setNat(i->getNat() - 1);
    }
}

void Battle::initTestBattle() {
    std::cout << "the Test battle is being initialized\n";
    this->theBattleActors.push_back(new BattleActor(true, 0, this));
    this->theBattleActors.push_back(new BattleActor(false, 1, this));
}

void Battle::onButtonPress() {
    if (IsKeyPressed(KEY_E)) {
        // party
        if (gui_currentScreen == 0) {
            // screen 0 is only party members there is nothing to select
            // update stuff to display here i guess
        }
            // actions
        else if (gui_currentScreen == 1) {
            switch (gui_currentAction) {
                case 0:
                case 1:
                case 2:
                    std::cout << "Attack " << gui_currentAction << std::endl;
                    theBattleActors[currentlyActingNumber]->setNextAttackFromMoveset(gui_currentAction);
                    theBattleActors[currentlyActingNumber]->autoTarget();
                    currentlyActingNumber++;
                    this->battleState = actorsActionSelection;
                    //Hier mus UI geschlossen werden I think.
                    break;

                case 3:
                    std::cout << "Wait" << std::endl;
                    currentlyActingPointer->setNextAttack(wait);
                    currentlyActingNumber++;
                    this->battleState = actorsActionSelection;

                    // infos in slot 4 ist in gui abgedeckt
            }
        }
            // items
        else if (gui_currentScreen == 2) {
            switch (gui_currentItem) {
                case 0:
                    std::cout << "Item 1" << std::endl;
                    break;

                case 1:
                    std::cout << "Item 2" << std::endl;
                    break;

                case 2:
                    std::cout << "Item 3" << std::endl;
                    break;

                    // infos in slot 4 ist in gui abgedeckt
            }
        }
    }
}
