#pragma once
#include "raylib.h"

struct controlInput{
	int up;
	int down;
	int left;
	int right;
	int confirm;
	int cancel;
	int opt1;
	int opt2;
};



void updateControls(controlInput* x);