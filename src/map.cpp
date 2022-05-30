#include "map.h"

#include "filesystem"
#include <iostream>

map::map()
{

	this->image = LoadImage("assets/graphics/backgrounds/map_test.png");
	ImageResizeNN(&this->image, this->image.width * 3, this->image.height * 3);
	this->texture = LoadTextureFromImage(this->image);
	this->position.x = 0;
	this->position.y = 0;

	this->player_start_pos.x = this->texture.width - 50;
	this->player_start_pos.y = this->texture.height - 30;

	//load tilesets
	std::ifstream tilesetDescriptionFile("assets/graphics/Tilesets/Tileset_Forest_Spirites_complet.json");
	this->tilesetDescription = nlohmann::json::parse(tilesetDescriptionFile);
	tilesetDescriptionFile.close();

	std::ifstream levelMapFile("assets/graphics/Maps/Level_mit_Interaktionsebene.json");
	this->levelMap = nlohmann::json::parse(levelMapFile);
	levelMapFile.close();

	//this->tileAtlasTexture = LoadTexture((tilesetDescription["image"].get<std::string>()).c_str());
	this->tileAtlasTexture = LoadTexture("assets/graphics/Tilesets/TilesetForestSpirites.png");

	this->vec = { 0, 0 };
	this->rec = { 0, 0, levelMap["tilewidth"], levelMap["tileheight"] };
}

map::~map()
{
	UnloadTexture(this->texture);
}

void map::draw()
{
	//jetzt wird das in jedem frame immer wieder neu geladen
	//in .h auslagern klappt nicht weil this-> einen error ausgibt


	for (auto const& layer : levelMap["layers"])
	{

		if (layer["type"] == "tilelayer" && layer["visible"])
		{

			for(auto const& tileId : layer["data"])
			{
				if (tileId != 0)
				{
					this->rec.x = (float)((((int)tileId - 1) % (int)tilesetDescription["columns"]) * (float)levelMap["tilewidth"]);
					this->rec.y = (float)floor((float)tileId / (float)tilesetDescription["columns"]) * (float)levelMap["tilewidth"];
					DrawTextureRec(this->tileAtlasTexture, this->rec, this->vec, WHITE);
					std::cout << "Drew a Tile: " << tileId << std::endl; //this is an output to help me understand what is happening
				}

				this->vec.x += (float)levelMap["tilewidth"];  //der vec zeigt wo in der welt das Tile hingedrawt wird.
				if (this->vec.x >= (float)layer["width"] * (float)levelMap["tilewidth"])
				{
					this->vec.x = 0;
					this->vec.y += (float)levelMap["tileheight"];
				}

			}

		}

	}

}