#include "map.h"

#include "filesystem"
#include <iostream>

map::map()
{
	this->tilemapData.tileMapWidth = 20;


	this->image = LoadImage("assets/graphics/backgrounds/map_test.png");
	ImageResizeNN(&this->image, this->image.width * 4, this->image.height * 4);
	this->texture = LoadTextureFromImage(this->image);
	this->position.x = 0;
	this->position.y = 0;

	this->player_start_pos.x = this->texture.width - 20; //need to parse from json
	this->player_start_pos.y = this->texture.height - 350;


	std::ifstream tilesetDescriptionFile("assets/graphics/Tilesets/Forest_Spirites_-_Testlevel_-_Tileset_v2.json"); //
	//Beginn des Parsens
	std::ifstream levelMapFile("assets/graphics/Maps/Forest_Spirits_-_Testlevel_V2"); //json file that says which tile number goes were
	this->levelMap = nlohmann::json::parse(levelMapFile);
	levelMapFile.close();
	this->mapData.mapWidth = levelMap["width"]; //schreibe in mapData die weite des Levels
	this->mapData.mapHeight = levelMap["height"];

	this->tileAtlasTexture = LoadTexture("assets/graphics/tilesets/Tileset_ForestSpirites_V2.png");

	//geh durch alle inhalte von layers
	for (auto const& layer : levelMap["layers"]) {
		//hier wird nach dem jeweiligen namen des layers gefragt
		//dann wird die id jedes tiles in die richtige struct geladen
		if (layer["name"] == "Ground") {
			for (auto const& tileID : layer["data"]) {
				mapData.layerGround.push_back(tileID-1);

			}
		}

		if (layer["name"] == "Interactables") {
			for (auto const& tileID : layer["data"]) {
				mapData.layerObjects.push_back(tileID-1);

			}
		}

		if (layer["name"] == "Decoration") {
			for (auto const& tileID : layer["data"]) {
				mapData.layerDecoration.push_back(tileID-1);

			}
		}

		if (layer["name"] == "Interactables") {
			for (auto const& tileID : layer["data"]) {
				mapData.layerObjects.push_back(tileID-1);

			}
		}

		//layerForegroundTransparent
		if (layer["name"] == "Foreground transparent") {
		for (auto const& tileID : layer["data"]) {
			mapData.layerForegroundTransparent.push_back(tileID-1);

		}
	}
		//layerForegroundOpaque
		if (layer["name"] == "Foreground") {
			for (auto const& tileID : layer["data"]) {
				mapData.layerForegroundOpaque.push_back(tileID-1);

			}
		}

		//collision doesnt work because of bool
		
		//layerCollision
		if (layer["name"] == "Collision") {
			for (auto const& tileID : layer["data"]) {
				if (tileID == 0)
				{
					mapData.layerCollision.push_back(false);
				}
				else
				{
					mapData.layerCollision.push_back(true);
				}
			}

			std::cout << "INFO: All Layers have been parsed." << std::endl;
		}
		
	}
	for (int i = 0; i < mapData.layerCollision.size(); i++) {
		if (mapData.layerCollision[i]) {
			Rectangle createdRectangle = { i % this->mapData.mapWidth * 128, i / this->mapData.mapWidth * 128, 128, 128 };
			collisionRectangles.push_back(createdRectangle);
		}
	}
	std::cout << "INFO: All collision  boxes were created" << std::endl;

}

map::~map()
{
	UnloadTexture(this->texture);
}

void map::drawBackground()
{
	for (int y{}; y < mapData.mapHeight; y++) {
		for (int x{}; x < mapData.mapWidth; x++) {
			DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerGround[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerGround[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
		}		
	}
	
	for (int y{}; y < mapData.mapHeight; y++) {
		for (int x{}; x < mapData.mapWidth; x++) {
			if (mapData.layerDecoration[x + y * mapData.mapWidth] != -1)
			DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerDecoration[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerDecoration[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
		}
	}
	
	for (int y{}; y < mapData.mapHeight; y++) {
		for (int x{}; x < mapData.mapWidth; x++) {
			if (mapData.layerObjects[x + y * mapData.mapWidth] != -1) {
				DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerObjects[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerObjects[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
			}
		}
	}
	
	

}

void map::drawForeground()
{

	for (int y{}; y < mapData.mapHeight; y++) {
		for (int x{}; x < mapData.mapWidth; x++) {
			if (mapData.layerForegroundTransparent[x + y * mapData.mapWidth] != -1)
			DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerForegroundTransparent[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerForegroundTransparent[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
		}
	}

	for (int y{}; y < mapData.mapHeight; y++) {
		for (int x{}; x < mapData.mapWidth; x++) {
			if (mapData.layerForegroundOpaque[x + y * mapData.mapWidth] != -1)
			DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerForegroundOpaque[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerForegroundOpaque[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
		}
	}

}

void map::drawCollision() {
	for (int i = 0; i < collisionRectangles.size(); i++) {
		DrawRectangleRec(collisionRectangles[i], RED);
	}
}