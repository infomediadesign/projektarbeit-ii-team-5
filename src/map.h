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
	void drawCollision();

	Image image;
	Texture2D texture;
	Vector2 position;

	Vector2 player_start_pos;

	/*//from tutorial to include tiled by Christoph
	Vector2 vec;
	Rectangle rec;
    //we dont use them*/

	//Here come Collision Rectangles Vector
	std::vector<Rectangle> collisionRectangles;

	nlohmann::json levelMap;
	Texture2D tileAtlasTexture;
	nlohmann::json tilesetDescription;
	//structs for tilemaps
	struct {
		Texture2D tileSet;
		int tileWidth;
		int tileMapWidth;
		int rowLength;
	} tileSetData;

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