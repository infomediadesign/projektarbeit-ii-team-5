#pragma once

#include "actor.h"
#include "map.h"
#include "forestSpiritsStructs.h"
#include "inventoryTemplate.h"
#include "itemBase.h"
#include "itemHeilbeere.h"

class player : public actor
{
public:
	player(map* current_map);
	~player();

    Texture2D textureAnimated;
    int framesCounter = 0;
    int framesOffset = 0;

    void update(controlInput controlInputs, std::vector<Rectangle>& walls);
    void draw();
    bool checkForAnyCollisions(std::vector<Rectangle> collisions);
    Rectangle getCollision();

protected:
	map* current_map;

    int currentSlot = 0;

    // add an inventory container with 12 slots
    inventoryTemplate<itemBase*, 12> inventory;
    itemHeilbeere* heilbeere = new itemHeilbeere;

    void movement(controlInput controlInputs,std::vector<Rectangle>& walls);
    void addItem(itemBase* item);

	//int movement_speed;


	
};