#pragma once

#include "actor.h"
#include "forestSpiritsStructs.h"
#include "raylib.h"

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

    Rectangle slot_positions[12];

	controlInput* controlInputs{};
	bool isVisible = false;
    int slot_offset = (32 + 16) * scale_factor;
    int current_slot = 0;

};