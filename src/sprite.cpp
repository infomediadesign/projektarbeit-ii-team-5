#include "sprite.h"
#include "raylib.h"

//die funktion wird in der sprite.h deklariert
void Sprite::Draw() {
	DrawTexture(texture, pos_x, pos_y, WHITE);
}

Sprite::Sprite(int pos_x, int pos_y, Texture2D texture) : pos_x(pos_x), pos_y(pos_y), texture(texture)
{
	//beliebiger Code hier
}

Sprite::~Sprite()
{
	UnloadTexture(texture);
}