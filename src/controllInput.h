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



void updateControls(controlInput* x) {
	//Upwards
	if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
		x->up++;
	else
		x->up = 0;
	//Downwards
	if (IsKeyDown(KEY_S) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
		x->down++;
	else
		x->down = 0;
	//Leftwards
	if (IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
		x->left++;
	else
		x->left = 0;
	//Rightwards
	if (IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
		x->right++;
	else
		x->right = 0;
	//Confirmwards
	if (IsKeyDown(KEY_ENTER) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
		x->confirm++;
	else
		x->confirm = 0;
	//Cancelwards
	if (IsKeyDown(KEY_RIGHT_SHIFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
		x->cancel++;
	else
		x->cancel = 0;
	//First option, Apostrophe equals "Ä"
	if (IsKeyDown(KEY_APOSTROPHE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
		x->opt1++;
	else
		x->opt1 = 0;
	//Second option, Slash equals "-"
	if (IsKeyDown(KEY_SLASH) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_UP))
		x->opt2++;
	else
		x->opt2 = 0;

}
	