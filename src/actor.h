#pragma once

#include <cstdlib>
#include "raylib.h"
#include "config.h"

class actor
{
public:
	Texture2D texture;
	Vector2 position;
	Image image;

	int movement_speed = 5;
	int scale_factor = 4;

	bool visible;

	//void update();
	//void draw();

	//later
	//hp
	//attack points
};