#pragma once

#include "actor.h"
#include "map.h"

class player : public actor
{
public:
	player(map* current_map);
	~player();
	
	map* current_map;

	Image bag_img; //should be drawn in relation to player
	Texture2D bag;

	//int movement_speed;

	void update();
	void draw();
	
};