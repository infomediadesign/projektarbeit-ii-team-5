#include "map.h"

#include "filesystem"
#include <iostream>

map::map()
{

	this->image = LoadImage("assets/graphics/backgrounds/map_test.png");
	ImageResizeNN(&this->image, this->image.width * 4, this->image.height * 4);
	this->texture = LoadTextureFromImage(this->image);
	this->position.x = 0;
	this->position.y = 0;

	this->player_start_pos.x = this->texture.width - 50; //need to parse from json
	this->player_start_pos.y = this->texture.height - 30;
	std::ifstream tilesetDescriptionFile("assets/graphics/Tilesets/Tileset_Forest_Spirites_complet.json"); //
	//Beginn des Parsens
	std::ifstream levelMapFile("assets/graphics/Maps/Level_mit_Interaktionsebene.json");
	this->levelMap = nlohmann::json::parse(levelMapFile);
	levelMapFile.close();
	this->mapData.mapWidth = levelMap["width"]; //schreibe in mapData die weite des Levels
	this->mapData.mapHeight = levelMap["height"];

	this->tileAtlasTexture = LoadTexture("assets/graphics/tilesets/TilesetForestSpirites.png");

	//geh durch alle inhalte von layers
	for (auto const& layer : levelMap["layers"]) {
		//hier wird nach dem jeweiligen namen des layers gefragt
		//dann wird die id jedes tiles in die richtige struct geladen
		if (layer["name"] == "Ground") {
			for (auto const& tileID : layer["data"]) {
				mapData.layerGround.push_back(tileID);

			}
		}


		//same for:

		//layerObjects
		//layerDecoration
		//layerForegroundTransparent
		//layerForegroundOpaque
		//layerCollision
		
	}
	
}

map::~map()
{
	UnloadTexture(this->texture);
}

void map::draw()
{
	//
	for (int y{}; y < mapData.mapHeight; y++) {
		for (int x{}; x < mapData.mapWidth; x++) {
			DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerGround[x + y * mapData.mapWidth] % 15) * 32,(float)(mapData.layerGround[x + y * mapData.mapWidth] / 15) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
		}
	}



}