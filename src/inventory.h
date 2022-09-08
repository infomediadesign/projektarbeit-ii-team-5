#pragma once

#include "actor.h"
#include "forestSpiritsStructs.h"
#include "raylib.h"
#include "inventoryTemplate.h"
#include "itemBase.h"
#include "itemHeilbeere.h"
#include "itemMudbomb.h"
#include "itemSeifenblase.h"

class inventory : public actor
{
public:
    inventory(controlInput* controlInputs);
    ~inventory();
    void update();
    void draw();
    bool isActive();

    // use this methods from player to add items
    void addMudbomb();
    void addHeilbeere();
    void addSeifenblase();

protected:

	Image bag_img;
	Texture2D backpack;
    Texture2D selection;
    void setSlots();
    void navigateInventory();
    void drawItems(int i);

    Rectangle slot_positions[12];

    controlInput* controlInputs{};

    // add an inventory container with 12 slots
    inventoryTemplate<itemBase*, 12> inventoryContainer;
    // add pointers to item objects
    itemHeilbeere* heilbeere = new itemHeilbeere;
    itemMudbomb* mudbomb = new itemMudbomb;
    itemSeifenblase* seifenblase = new itemSeifenblase;

    void addItem(itemBase* item);

    int container_slot = 0;

	bool isVisible = false;
    int slot_offset = (32 + 16) * scale_factor;
    int current_slot = 0;

};














