#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

#include "actor.h"

class map : public actor
{
public:
	map();
	~map();

	void drawBackground();
	void drawForeground();
	void addCollision();

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
	//structs for tilemaps
	struct {
		Texture2D tilemap;
		int tileWidht;
		int tileMapWidth;
		int rowLength;
	} tilemapData;

	struct {
		std::vector<int> layerGround;
		std::vector<int> layerObjects; //each non-0 tile references an Event.
		std::vector<int> layerDecoration; 
		std::vector<int> layerForegroundTransparent;
		std::vector<int> layerForegroundOpaque;
		std::vector<bool> layerCollision; //saves walls and what not
		int mapWidth;
		int mapHeight;
	} mapData;
};