#pragma once

#include "actor.h"

class inventory : public actor
{
public:

	inventory();
	~inventory();

	Image bag_img;
	Texture2D bag_c_texu;
	Texture2D bag_o_texu;

	bool visible = false;

	void update();
	void draw();
};