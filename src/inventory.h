#pragma once

#include "actor.h"

class inventory : public actor
{
public:

	inventory();
	~inventory();

	bool is_open = false;
	bool visible = false;

	void open();
	void close();
	void update();
	void draw();
};