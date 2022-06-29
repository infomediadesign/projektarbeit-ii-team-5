#pragma once
#include <vector>

class Battle {
	//attributes
private:
	std::vector<BattleActor> BattleActors;
	int currentTurn = 0;
	int currentTurnStep;
	int waitingForAnimtaion = 0;

public:
	


	//methods
private:
	void decreaseAllNats();
	void calculatePrognosis();
public:
	Battle(int advantage, int encounternumber, ); //constructor
	void frameRoutine(); //wird jeden frame aufgerufen
	void drawBattle();
	BattleActor* getRandomPlayerPointer(int target);
};