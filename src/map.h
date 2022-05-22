#pragma once

#include "actor.h"

class map : public actor
{
public:
	map();
	~map();

	Image image;
	Texture2D texture;
	Vector2 position;

	Vector2 player_start_pos;
};