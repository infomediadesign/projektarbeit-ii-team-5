#include "inventory.h"
#include "player.h"

inventory::inventory()
{
	//image initialization
	//this->image = LoadImage("assets/graphics/inventory_test.png");
	//ImageResizeNN(&this->image, this->image.width * this->scale_factor, this->image.height * 3);
	//this->texture = LoadTextureFromImage(this->image);
	this->texture = LoadTexture("assets/graphics/inventory_test.png");
	this->position.x = 0;
	this->position.y = 0;
}

inventory::~inventory()
{
	UnloadTexture(this->texture);
}

//checks if inventory was opened
void inventory::open()
{
	this->is_open = true;
	this->visible = true;
}

//checks if inventory was closed
void inventory::close()
{
	if (this->is_open == true)
	{
		this->visible = false;
	}
}

void inventory::update()
{
	/*
	if (IsKeyDown(KEY_I))
	{
		this->visible = true;
	}
	else
	{
		this->visible = false;
	}
	/*
	if (IsKeyPressed(KEY_I) && this->is_open == false)
	{
		this->open();
	}
	else if (IsKeyPressed(KEY_I) && this->is_open == true)
	{
		this->close();
	}
	*/
}

void inventory::draw()
{
	if (this->visible == true)
	{
		DrawTexture(this->texture, this->position.x - this->texture.width/2, this->position.y - this->texture.height/2, WHITE);
	}
	
}