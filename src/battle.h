#pragma once
#include <vector>
#include "BattleActor.h"
#include <string>
#include <memory>
#include "forestSpiritsStructs.h"

enum enumBattleState{
    startOfTick = 0,
    actorsActionSelection = 1,
    playerActionSelect = 2,
    playOutRound = 3,
    textBubble = 4,
    playingAnimation = 5,
    winningScreen = 6
};

enum GUI_Box{
    gui_actors,
    gui_attacks,
    gui_items
};

class battleButton{
public:
    battleButton* aboveButton;
    battleButton* belowButton;
    int getConfirmIndex(){return this->confirmIndex;}
private:
    int confirmIndex;
};
class battleMenu{
    battleMenu* cancelMenu;
    std::vector<battleButton> buttons;
    battleButton* selectedButton;
};

class Battle {
	//attributes
private:
	std::vector<BattleActor*> theBattleActors{};

	int waitingForAnimtaion = 0;
	bool isWaitingForPlayerInput{};
	BattleActor* currentlyActingPointer{};
    enumBattleState battleState = startOfTick;
    int currentTurn = 0;
    int currentlyActingNumber = 0; //secondary state switch
    std::string infoText = "";
public:
	controlInput* controlInputs{};
    bool killMe = false;


	//methods
private:
	void decreaseAllNats();
	void calculatePrognosis(); 
	void receiveUIAnswer(std::string);
	BattleActor* getRandomPlayerPointer(int target);
    void playTurn();
public:
	Battle(int advantage, int encounternumber); //constructor
	void frameRoutine(); //wird jeden frame aufgerufen
	void drawBattle();
	bool toBeDestroyed();
    void initTestBattle();

    // GUI Stuff
protected:
    Texture2D background;
    Texture2D baseActors;
    Texture2D baseAttacks;
    Texture2D baseItems;

    GUI_Box gui_currentBox = gui_actors;

public:
    void draw();
    void drawGUIBox(Texture2D texture);
    void update_gui();
};