#pragma once
#include <vector>
#include "BattleActor.h"
#include <string>

enum enumBattleState{
    startOfTick = 0,
    actorsActionSelection = 1,
    playerActionSelect = 2,
    playOutRound = 3,
    textBubble = 4,
    playingAnimation = 5,
    winningScreen = 6
};

class Battle {
	//attributes
private:
	std::vector<BattleActor> theBattleActors;
	int currentTurn = 0;
	int waitingForAnimtaion = 0;
	bool isWaitingForPlayerInput;
	BattleActor* currentlyActing;
    enumBattleState battleState;
public:
	


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
};