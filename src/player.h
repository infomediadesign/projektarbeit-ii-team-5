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
    Rectangle getCollision(int direction);

protected:
	map* current_map;
    inventory* inventory_pointer = new inventory(controlInputs);

    int currentSlot = 0;

    void movement(std::vector<Rectangle>& walls);
    void addItem(itemBase* item);

	//int movement_speed;



    bool checkForAnyCollisions(std::vector<Rectangle> walls, int direction);
};