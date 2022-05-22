#pragma once
#include "raylib.h"

class Sprite
{
public:
	int pos_x;
	int pos_y;
	Texture2D texture;

	Sprite() = delete;
	Sprite(int pos_x, int pos_y, Texture2D texture);

	~Sprite();

	//die wird in der .cpp zum header initialisiert
	void Draw();


};