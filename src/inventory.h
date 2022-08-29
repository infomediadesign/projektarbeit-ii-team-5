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

    Rectangle slot_positions[12];

	controlInput* controlInputs{};
	bool isVisible = false;
    int slot_offset_x = (32 + 16) * scale_factor;
    int slot_offset_y = 0;
    int current_slot = 0;

};