#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

#include "actor.h"

class map : public actor
{
public:
	map();
	~map();

	void draw();

	Image image;
	Texture2D texture;
	Vector2 position;

	Vector2 player_start_pos;

	//from tutorial to include tiled by Christoph
	Vector2 vec;
	Rectangle rec;

	nlohmann::json levelMap;
	Texture2D tileAtlasTexture;
	nlohmann::json tilesetDescription;

	
};