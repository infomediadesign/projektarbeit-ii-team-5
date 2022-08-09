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
};