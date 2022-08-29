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

	controlInput* controlInputs{};
	bool isVisible = false;
    int scaleFactor = 4;

};