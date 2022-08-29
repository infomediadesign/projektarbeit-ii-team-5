#pragma once

#include "actor.h"
#include "forestSpiritsStructs.h"
#include "raylib.h"
#include "inventoryTemplate.h"
#include "itemBase.h"
#include "itemHeilbeere.h"
#include "itemMudbomb.h"

class inventory : public actor
{
public:
    inventory(controlInput* controlInputs);
    ~inventory();
    void update();
    void draw();
    bool isActive();

protected:

	Image bag_img;
	Texture2D bag_closed;
	Texture2D bag_open;
    Texture2D selection;
    void setSlots();
    void navigateInventory();
    void drawItems(int i);

    Rectangle slot_positions[12];

    controlInput* controlInputs{};

    // add an inventory container with 12 slots
    inventoryTemplate<itemBase*, 12> inventoryContainer;
    itemHeilbeere* heilbeere = new itemHeilbeere;
    itemMudbomb* mudbomb = new itemMudbomb;

    void addItem(itemBase* item);

    int container_slot = 0;

	bool isVisible = false;
    int slot_offset = (32 + 16) * scale_factor;
    int current_slot = 0;

};