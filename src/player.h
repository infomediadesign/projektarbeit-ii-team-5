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

    void update(controlInput controlInputs, std::vector<Rectangle>& walls);
    void draw();
    bool checkForAnyCollisions(std::vector<Rectangle> collisions);
    Rectangle getCollision();

protected:
	map* current_map;

    void movement(controlInput controlInputs,std::vector<Rectangle>& walls);

	//int movement_speed;


	
};