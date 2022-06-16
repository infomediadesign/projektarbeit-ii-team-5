#pragma once

#include "actor.h"
#include "map.h"
#include "controllInput.h"

class player : public actor
{
public:
	player(map* current_map);
	~player();

	

	bool facingDirection; //true == up, false == down
	
	map* current_map;

	//int movement_speed;

	void update(controlInput controlInputs, std::vector<Rectangle> walls);
	void draw();
	bool checkForAnyCollisions(std::vector<Rectangle> collisions);
	Rectangle getCollision();
	
};