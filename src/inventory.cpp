#include "inventory.h"

#include <iostream>

inventory::inventory(controlInput* x)
{
    // inventory
    this->scale_factor = 4;
	this->texture = LoadTexture("assets/graphics/UI/Inventory/Inventory.png");
	this->position.x = GetScreenWidth()/2 - texture.width*scale_factor/2;
	this->position.y = GetScreenHeight()/2 - texture.height*scale_factor/2;

    this->backpack = LoadTexture("assets/graphics/UI/Inventory/Backpack.png");
    this->selection = LoadTexture("assets/graphics/UI/Inventory/Slot_Selection.png");
    this->infobox = LoadTexture("assets/graphics/UI/Inventory/InfosBox.png");

    this->controlInputs = x;

    this->setSlots();

    return;
}

inventory::~inventory()
{
	UnloadTexture(this->texture);
	UnloadTexture(this->backpack);

}

void inventory::update()
{
    /*
	if (IsKeyPressed(KEY_N))
    {
        deleteItems();
    }
    */

	if (this->controlInputs->opt1 == 1)
	{
		this->isVisible = !this->isVisible;
		std::cout << "Inventory bool has been flipped to: " << this->isVisible << std::endl;
	}


    // add items manually for debug
    if (IsKeyPressed(KEY_M))
    {
        addItem(heilbeere);
        addItem(seifenblase);
        addItem(mudbomb);
        addItem(seifenblase);
        addItem(mudbomb);
        addItem(heilbeere);
        addItem(heilbeere);
        addItem(mudbomb);
    }


    navigateInventory();
}

void inventory::draw()
{
    // always draw backpack aber je nach dem ob open oder nicht ein anderers source rectangle
    DrawTexturePro(this->backpack,
                   {(float)isVisible * 16, 0, 16, 16},
                   {(float)GetScreenWidth() - (backpack.width * 10)/2, (float)GetScreenHeight() - (backpack.width * 10)/2, (float)16*10, (float)16 * 10},
                   {16*2, 16*2}, 0, WHITE);

	if (this->isVisible == true)
	{

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

        if (isInfo)
        {
            DrawTexturePro(this->infobox,
                           {0, 0, (float)this->infobox.width, (float)this->infobox.height},
                           {(float)GetScreenWidth()/2 - this->infobox.width/2*this->scale_factor, (float)GetScreenHeight() / 2 - this->infobox.height / 2 * this->scale_factor, (float)this->infobox.width * this->scale_factor, (float)this->infobox.height * this->scale_factor},
                           {0, 0} ,0, WHITE);

            drawInfobox();
        }



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

    info_positions[0] = {(float)GetScreenWidth()/2 - 350, (float)GetScreenHeight() / 2 - 100};
    info_positions[1] = {info_positions[0].x, info_positions[0].y + 60};
    info_positions[2] = {info_positions[0].x, info_positions[1].y + 60};
}

void inventory::drawItems(int i)
{
    // draw every occupied slot
    if (this->container_slot > i && this->container_slot < 12)
    {
        DrawTexturePro(inventoryContainer.getItem(i)->GetTexture(),
                       {0, 0, (float)inventoryContainer.getItem(i)->GetTexture().width, (float)inventoryContainer.getItem(i)->GetTexture().height},
                       slot_positions[i],
                       {0, 0}, 0, WHITE);
    }
}

void inventory::navigateInventory()
{
    if (isVisible == true)
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

        // open/close infos
        if (isInfo == true && IsKeyPressed(KEY_SPACE) || isInfo == true && IsKeyPressed(KEY_I))
        {
            isInfo = false;
        }
        else if (isInfo == false && IsKeyPressed(KEY_SPACE))
        {
            isInfo = true;
        }
    }
}

void inventory::drawInfobox()
{
    if (current_slot <= container_slot - 1)
    {
        // print info accessing the Inventory item
        DrawText(("Slot: " + std::to_string(this->current_slot + 1)).c_str(), this->info_positions[0].x, this->info_positions[0].y, 40, GetColor(0xb9824bff));
        DrawText(("Name: " + inventoryContainer.getItem(current_slot)->GetName()).c_str(), this->info_positions[1].x, this->info_positions[1].y, 40, GetColor(0xb9824bff));
        DrawText(("Description: " + (inventoryContainer.getItem(current_slot)->GetDescription())).c_str(), this->info_positions[2].x, this->info_positions[2].y, 40, GetColor(0xb9824bff));
    }
    else
    {
        // print default
        DrawText(("Slot: " + std::to_string(this->current_slot +1)).c_str(), this->info_positions[0].x, this->info_positions[0].y, 40, WHITE);
    }
}

void inventory::deleteItems()
{
    for (int i = 0; i < 10; i++)
    {
        container_slot = 0;
        inventoryContainer.setItem(NULL, i);
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