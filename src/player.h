#pragma once

#include "actor.h"
#include "map.h"
#include "forestSpiritsStructs.h"
#include "inventory.h"

class player : public actor
{
public:
	player(map* current_map);
	~player();

    Texture2D textureAnimated;
    int framesCounter = 0;
    int framesOffset = 0;

    controlInput* controlInputs = nullptr;

    void update(controlInput controlInputs, std::vector<Rectangle>& walls);
    void draw();
    bool checkForAnyCollisions(std::vector<Rectangle> collisions);
    Rectangle getCollision();

protected:
	map* current_map;
    inventory* Inventory = new inventory(controlInputs);

    int currentSlot = 0;

    void movement(std::vector<Rectangle>& walls);
    void addItem(itemBase* item);

	//int movement_speed;


	
};