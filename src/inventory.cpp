#include "inventory.h"
#include "player.h"
#include <iostream>

inventory::inventory(controlInput* x)
{
	//image initialization
	this->image = LoadImage("assets/graphics/backgrounds/UI/Inventory/InventoryTest.png");
	ImageResizeNN(&this->image, this->image.width * 2, this->image.height * 2);
	this->texture = LoadTextureFromImage(this->image);
	//this->texture = LoadTexture("assets/graphics/backgrounds/UI/Inventory/InventoryBlank.png");
	this->position.x = 0;
	this->position.y = 0;

	this->bag_img = LoadImage("assets/graphics/backgrounds/UI/Inventory/BagClosed.png");
	ImageResizeNN(&this->bag_img, this->bag_img.width * 2, this->bag_img.height * 2);
	this->bag_c_texu = LoadTextureFromImage(this->bag_img);

	this->bag_img = LoadImage("assets/graphics/backgrounds/UI/Inventory/BagOpen.png");
	ImageResizeNN(&this->bag_img, this->bag_img.width * 2, this->bag_img.height * 2);
	this->bag_o_texu = LoadTextureFromImage(this->bag_img);
	this->controlInputs = x;
	return;
}

inventory::~inventory()
{
	UnloadTexture(this->texture);
	UnloadTexture(this->bag_c_texu);
	UnloadTexture(this->bag_o_texu);
}

void inventory::update()
{
	
	if (this->controlInputs->opt1 == 1)
	{
		this->visible = !this->visible;
		std::cout << "Inventory bool has been flipped to: " << this->visible << std::endl;
	}
}

void inventory::draw()
{
	if (this->visible == true)
	{
		DrawTexture(this->bag_o_texu, Game::ScreenWidth - 150, Game::ScreenHeight - 150, WHITE);
		DrawTexture(this->texture, Game::ScreenWidth/2 - this->texture.width/2, Game::ScreenHeight/2 - this->texture.height/2, WHITE);
	}
	else
	{
		DrawTexture(this->bag_c_texu, Game::ScreenWidth - 150, Game::ScreenHeight - 150, WHITE);
	}

	
	
}