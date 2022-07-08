#pragma once

#include "actor.h"
#include "forestSpiritsStructs.h"

class inventory : public actor
{
public:

	inventory(controlInput* controlInputs);
	~inventory();

	Image bag_img;
	Texture2D bag_c_texu;
	Texture2D bag_o_texu;

	controlInput* controlInputs{};
	bool visible = false;

	void update();
	void draw();
};