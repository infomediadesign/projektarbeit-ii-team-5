#include "inventory.h"
#include "player.h"
#include <iostream>

inventory::inventory(controlInput* x)
{
    // inventory
    this->scale_factor = 4;
	this->texture = LoadTexture("assets/graphics/UI/Inventory/Inventory.png");
	this->position.x = GetScreenWidth()/2 - texture.width*scale_factor/2;
	this->position.y = GetScreenHeight()/2 - texture.height*scale_factor/2;

    this->bag_closed = LoadTexture("assets/graphics/UI/Inventory/BagClosed.png");
    this->bag_open = LoadTexture("assets/graphics/UI/Inventory/BagOpen.png");
    this->selection = LoadTexture("assets/graphics/UI/Inventory/Slot_Selection.png");

    this->controlInputs = x;

    this->setSlots();

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

    if (IsKeyPressed(KEY_D) && current_slot < 3)
    {
        this->current_slot++;
    }
    else if (IsKeyPressed(KEY_A) && current_slot > 0)
    {
        this->current_slot--;
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
                       Rectangle{(float)position.x,  (float)position.y,(float) this->texture.width*scale_factor,(float) this->texture.height*scale_factor},
                       {0, 0}, 0.0, WHITE);

        DrawTexturePro(this->selection,
                       {0, 0, (float)this->selection.width, (float)this->selection.height},
                       this->slot_positions[this->current_slot],
                       {0, 0}, 0, WHITE);
	}
	else
	{
        DrawTexturePro(this->bag_closed,
                       Rectangle{0, 0, (float)this->bag_open.width, (float)this->bag_open.height},
                       Rectangle{(float)GetScreenWidth() - ((GetScreenWidth() -Game::ScreenWidth)/2) - 150,  (float)GetScreenHeight() - 150 , (float)(int)this->bag_open.width * 2, (float)this->bag_open.height * 2},
                       {0, 0}, 0.0, WHITE);
	}
}

void inventory::setSlots()
{
    this->slot_positions[0] = {position.x + 16*scale_factor, position.y + 32*scale_factor, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[1] = {slot_positions[0].x + this->slot_offset_x, slot_positions[0].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[2] = {slot_positions[1].x + this->slot_offset_x, slot_positions[1].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[3] = {slot_positions[2].x + this->slot_offset_x, slot_positions[2].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
}

bool inventory::isActive() { return this->isVisible; }