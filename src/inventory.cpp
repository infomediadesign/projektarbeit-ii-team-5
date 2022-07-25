#include "inventory.h"
#include "player.h"
#include <iostream>

inventory::inventory(controlInput* x)
{
    // inventory
	this->texture = LoadTexture("assets/graphics/UI/Inventory/InventoryTest.png");
	this->position.x = 0;
	this->position.y = 0;

    this->bag_c_texu = LoadTexture("assets/graphics/UI/Inventory/BagClosed.png");
    this->bag_o_texu = LoadTexture("assets/graphics/UI/Inventory/BagOpen.png");

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
        DrawTexturePro(this->bag_o_texu,
                       Rectangle{0, 0, this->bag_o_texu.width, this->bag_o_texu.height},
                       Rectangle{GetScreenWidth() - ((GetScreenWidth() -Game::ScreenWidth)/2) - 150,  GetScreenHeight() - 150 , (int)this->bag_o_texu.width * 2, this->bag_o_texu.height*2},
                       {0, 0}, 0.0, WHITE);

        DrawTexturePro(this->texture,
                       Rectangle{0, 0, this->texture.width, this->texture.height},
                       Rectangle{0,  0, this->texture.width*2, this->texture.height*2},
                       {0, 0}, 0.0, WHITE);

		//DrawTexture(this->bag_o_texu, , GetScreenHeight() - 150, WHITE);
		//DrawTexture(this->texture, Game::ScreenWidth/2 - this->texture.width/2, Game::ScreenHeight/2 - this->texture.height/2, WHITE);
	}
	else
	{
        DrawTexturePro(this->bag_c_texu,
                       Rectangle{0, 0, this->bag_o_texu.width, this->bag_o_texu.height},
                       Rectangle{GetScreenWidth() - ((GetScreenWidth() -Game::ScreenWidth)/2) - 150,  GetScreenHeight() - 150 , (int)this->bag_o_texu.width * 2, this->bag_o_texu.height*2},
                       {0, 0}, 0.0, WHITE);
	}

	
	
}