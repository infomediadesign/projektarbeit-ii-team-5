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

    int actor_frames = 0;
    int actor_frame_offset = 0;
    Texture2D player;
    Texture2D shroom;
    void drawBattlePlayer(Texture2D texture, Vector2 position);
    void drawBattleEnemy(Texture2D texture, Vector2 position);
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
    Texture2D marker_1;
    Texture2D marker_2;
    Texture2D markerItems;
    Texture2D infoActions;
    Texture2D infoItems;

    Vector2 box1Positions[3];
    Vector2 boxActionsPositions[5];
    Vector2 boxItemsPosition[4];
    Rectangle boxInfoPosition;

    int gui_currentScreen = 0;
    int gui_currentBox = 0;
    int gui_currentAction = 0;
    int gui_currentItem = 0;
    int gui_scaleFactor = 5;

    // bool isActorSelectVisible = false;
    bool isActionSelectVisible = false;
    bool isItemSelectVisible = false;
    bool showActionInfo = false;
    bool showItemInfo = false;

    void gui_setSlots();
    void drawGUIBox(Texture2D texture);
    void drawGUISelection(Texture2D texture, Vector2 position);


public:
    void draw();
    void resetGUI();
    void update_gui();
};