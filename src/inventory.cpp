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

    if (IsKeyPressed(KEY_J) && container_slot < 12)
    {
        addItem(heilbeere);
    }
    else if (IsKeyPressed(KEY_K) && container_slot < 12)
    {
        addItem(mudbomb);
    }
    else if (IsKeyPressed(KEY_L) && container_slot < 12)
    {
        addItem(seifenblase);
    }

    navigateInventory();
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


        // go through every slot and draw every single item
        for (int i = 0; i < 12; i++)
        {
            drawItems(i);
        }

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
    // all slot positions depend on the slot before them
    // first one in each row always sets the y value, then there is only x offset

    // first row
    this->slot_positions[0] = {position.x + 16*scale_factor, position.y + 32*scale_factor, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[1] = {slot_positions[0].x + this->slot_offset, slot_positions[0].y, (float)selection.width * scale_factor, (float)selection.height * scale_factor};
    this->slot_positions[2] = {slot_positions[1].x + this->slot_offset, slot_positions[1].y, (float)selection.width * scale_factor, (float)selection.height * scale_factor};
    this->slot_positions[3] = {slot_positions[2].x + this->slot_offset, slot_positions[2].y, (float)selection.width * scale_factor, (float)selection.height * scale_factor};

    // second row
    this->slot_positions[4] = {slot_positions[0].x, slot_positions[0].y + slot_offset, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[5] = {slot_positions[4].x + slot_offset, slot_positions[4].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[6] = {slot_positions[5].x + slot_offset, slot_positions[5].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[7] = {slot_positions[6].x + slot_offset, slot_positions[6].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};

    // third row
    this->slot_positions[8] = {slot_positions[0].x, slot_positions[4].y + slot_offset, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[9] = {slot_positions[8].x + slot_offset, slot_positions[8].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[10] = {slot_positions[9].x + slot_offset, slot_positions[9].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
    this->slot_positions[11] = {slot_positions[10].x + slot_offset, slot_positions[10].y, (float)selection.width*scale_factor, (float)selection.height*scale_factor};
}

void inventory::drawItems(int i)
{
    // draw every occupied slot
    if (this->container_slot > i)
    {
        DrawTexturePro(inventoryContainer.getItem(i)->GetTexture(),
                       {0, 0, (float)inventoryContainer.getItem(i)->GetTexture().width, (float)inventoryContainer.getItem(i)->GetTexture().height},
                       slot_positions[i],
                       {0, 0}, 0, WHITE);
    }
}

void inventory::navigateInventory()
{
    // inventory slot navigation
    if (IsKeyPressed(KEY_D) && current_slot < 11)
    {
        this->current_slot++;
    }
    else if (IsKeyPressed(KEY_A) && current_slot > 0)
    {
        this->current_slot--;
    }
    else if (IsKeyPressed(KEY_S))
    {
        switch (current_slot)
        {
            // first row
            case 0:
                current_slot = 4;
                break;

            case 1:
                current_slot = 5;
                break;

            case 2:
                current_slot = 6;
                break;

            case 3:
                current_slot = 7;
                break;

                //second row
            case 4:
                current_slot = 8;
                break;

            case 5:
                current_slot = 9;
                break;

            case 6:
                current_slot = 10;
                break;

            case 7:
                current_slot = 11;

        }
    }
    else if (IsKeyPressed(KEY_W))
    {
        switch (current_slot)
        {
            // second row
            case 4:
                current_slot = 0;
                break;

            case 5:
                current_slot = 1;
                break;

            case 6:
                current_slot = 2;
                break;

            case 7:
                current_slot = 3;

            // third row
            case 8:
                current_slot = 4;
                break;

            case 9:
                current_slot = 5;
                break;

            case 10:
                current_slot = 6;
                break;

            case 11:
                current_slot = 7;
        }
    }
}

void inventory::addMudbomb(){ addItem(mudbomb);}
void inventory::addHeilbeere() { addItem(heilbeere);}
void inventory::addSeifenblase() { addItem(seifenblase);}

void inventory::addItem(itemBase *item)
{
    inventoryContainer.setItem(item, container_slot);
    container_slot++;
}

bool inventory::isActive() { return this->isVisible; }