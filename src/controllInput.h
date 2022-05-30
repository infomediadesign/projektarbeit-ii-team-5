#pragma once
#include "raylib.h"

struct{
	int up;
	int down;
	int left;
	int right;
	int confirm;
	int cancel;
	int opt1;
	int opt2;
}controlInputs; //Das ist ine globale Variable.

void updateControls() {
	//Upwards
	if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
		controlInputs.up++;
	else
		controlInputs.up = 0;
	//Downwards
	if (IsKeyDown(KEY_S) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
		controlInputs.down++;
	else
		controlInputs.down = 0;
	//Leftwards
	if (IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
		controlInputs.left++;
	else
		controlInputs.left = 0;
	//Rightwards
	if (IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
		controlInputs.right++;
	else
		controlInputs.right = 0;
	//Confirmwards
	if (IsKeyDown(KEY_ENTER) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
		controlInputs.confirm++;
	else
		controlInputs.confirm = 0;
	//Cancelwards
	if (IsKeyDown(KEY_RIGHT_SHIFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
		controlInputs.cancel++;
	else
		controlInputs.cancel = 0;
	//First option, Apostrophe equals "Ä"
	if (IsKeyDown(KEY_APOSTROPHE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
		controlInputs.opt1++;
	else
		controlInputs.opt1 = 0;
	//Second option, Slash equals "-"
	if (IsKeyDown(KEY_SLASH) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_UP))
		controlInputs.opt2++;
	else
		controlInputs.opt2 = 0;

}
	