#pragma once

#include "actor.h"
#include "map.h"
#include "forestSpiritsStructs.h"

class player : public actor
{
public:
	player(map* current_map);
	~player();

    Texture2D textureAnimated;
    int framesCounter = 0;
    int framesOffset = 0;
	
	map* current_map;

	//int movement_speed;

	void update(controlInput controlInputs, std::vector<Rectangle>& walls);
	void draw();
	bool checkForAnyCollisions(std::vector<Rectangle> collisions);
	Rectangle getCollision();
	
};