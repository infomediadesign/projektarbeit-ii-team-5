#include "inventory.h"
#include "player.h"
#include <iostream>

inventory::inventory(controlInput* x)
{
    // inventory
	this->texture = LoadTexture("assets/graphics/UI/Inventory/Inventory.png");
	this->position.x = 0;
	this->position.y = 0;

    this->bag_closed = LoadTexture("assets/graphics/UI/Inventory/BagClosed.png");
    this->bag_open = LoadTexture("assets/graphics/UI/Inventory/BagOpen.png");

    this->controlInputs = x;
    return;
}

inventory::~inventory()
{
	UnloadTexture(this->texture);
	UnloadTexture(this->bag_closed);
	UnloadTexture(this->bag_open);
}

void inventory::update()
{
	
	if (this->controlInputs->opt1 == 1)
	{
		this->isVisible = !this->isVisible;
		std::cout << "Inventory bool has been flipped to: " << this->isVisible << std::endl;
	}
}

void inventory::draw()
{
	if (this->isVisible == true)
	{
        DrawTexturePro(this->bag_open,
                       Rectangle{0, 0, (float)this->bag_open.width, (float) this->bag_open.height},
                       Rectangle{(float)GetScreenWidth() - ((GetScreenWidth() -Game::ScreenWidth)/2) - 150,  (float)GetScreenHeight() - 150 , (float) (int)this->bag_open.width * 2, (float) this->bag_open.height * 2},
                       {0, 0}, 0.0, WHITE);

        DrawTexturePro(this->texture,
                       Rectangle{0, 0,(float) this->texture.width,(float) this->texture.height},
                       Rectangle{(float)GetScreenWidth()/2 - texture.width*scaleFactor/2,  (float)GetScreenHeight()/2 - texture.height*scaleFactor/2,(float) this->texture.width*scaleFactor,(float) this->texture.height*scaleFactor},
                       {0, 0}, 0.0, WHITE);
	}
	else
	{
        DrawTexturePro(this->bag_closed,
                       Rectangle{0, 0, (float)this->bag_open.width, (float)this->bag_open.height},
                       Rectangle{(float)GetScreenWidth() - ((GetScreenWidth() -Game::ScreenWidth)/2) - 150,  (float)GetScreenHeight() - 150 , (float)(int)this->bag_open.width * scaleFactor, (float)this->bag_open.height * scaleFactor},
                       {0, 0}, 0.0, WHITE);
	}
}

bool inventory::isActive() { return this->isVisible; }