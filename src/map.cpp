#include "map.h"

map::map()
{

	this->image = LoadImage("assets/graphics/backgrounds/map_test.png");
	ImageResizeNN(&this->image, this->image.width * 3, this->image.height * 3);
	this->texture = LoadTextureFromImage(this->image);
	this->position.x = 0;
	this->position.y = 0;

	this->player_start_pos.x = this->texture.width - 50;
	this->player_start_pos.y = this->texture.height - 30;
}

map::~map()
{
	UnloadTexture(this->texture);
}