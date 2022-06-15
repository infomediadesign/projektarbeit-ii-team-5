#pragma once

#include <cstdlib>
#include "raylib.h"
#include "config.h"

class actor
{
public:
	Texture2D texture;
	Texture2D texture2;
	Texture2D movement_texture;
	Vector2 position;
	Image image;
	Image image2;
	Image movement_img;

	//movement animation
	int current_frame;
	int frames_counter;
	int frame_speed = 8;
	Rectangle frame_rec = { 0.0f, 0.0f, (float)movement_texture.width / frame_speed, (float)movement_texture.height };

	int movement_speed = 5;
	int scale_factor = 4;

	bool visible;

	//void update();
	//void draw();

	//later
	//hp
	//attack points
};