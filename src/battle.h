#pragma once
#include <vector>
#include "BattleActor.h"
#include <string>

class Battle {
	//attributes
private:
	std::vector<BattleActor> theBattleActors;
	int currentTurn = 0;
	int currentTurnStep;
	int waitingForAnimtaion = 0;
	bool waitingForPlayerInput;
	BattleActor* currentlyActing;
public:
	


	//methods
private:
	void decreaseAllNats();
	void calculatePrognosis(); 
	void receiveUIAnswer(std::string);
	BattleActor* getRandomPlayerPointer(int target);
public:
	Battle(int advantage, int encounternumber); //constructor
	void frameRoutine(); //wird jeden frame aufgerufen
	void drawBattle();
	bool toBeDestroyed();
};