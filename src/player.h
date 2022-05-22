#pragma once

#include "actor.h"
#include "map.h"

class player : public actor
{
public:
	player(map* current_map);
	~player();
	
	map* current_map;

	//int movement_speed;

	void update();
	void draw();
	
};