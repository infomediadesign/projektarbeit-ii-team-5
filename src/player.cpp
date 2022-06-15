#include "player.h"
#include "map.h"

player::player(map* current_map) : current_map(current_map)
{
    this->image = LoadImage("assets/graphics/Sprites/Character/MainCharacter/Player_Front.png");
    ImageResizeNN(&this->image, this->image.width * scale_factor, this->image.height * scale_factor);
	this->texture = LoadTextureFromImage(this->image); //walking down

    this->image2 = LoadImage("assets/graphics/Sprites/Character/MainCharacter/Player_Back.png");
    ImageResizeNN(&this->image2, this->image2.width * scale_factor, this->image2.height * scale_factor);
    this->texture2 = LoadTextureFromImage(this->image2); //walking up

	//this->position.x = Game::ScreenWidth / 2 - this->texture.width / 2;
    this->position.x = current_map->player_start_pos.x - 80;
    this->position.y = current_map->player_start_pos.y- 1700;

}

player::~player()
{
	UnloadTexture(this->texture);
}

void player::update()
{
    //movement
    // 
    //press W A S D to move
    //stop at borders
    // 
    //right
    if (IsKeyDown(KEY_D) && this->position.x <= player::current_map->texture.width - this->texture.width)
    {
        this->position.x += this->movement_speed;
    }
    //left
    //else 
    if (IsKeyDown(KEY_A) && this->position.x >= 0)
    {
        this->position.x -= this->movement_speed;
    }
    //up
    //else 
    if (IsKeyDown(KEY_W) && this->position.y >= 0)
    {
        this->position.y -= this->movement_speed;
        this->facingDirection = true;
    }
    //down
    //else
    if (IsKeyDown(KEY_S) && this->position.y <= player::current_map->texture.height - this->texture.height)
    {
        this->position.y += this->movement_speed;
        this->facingDirection = false;
    }
}

void player::draw()
{
    if (this->facingDirection == false)
    {
        DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
    }

    else if (this->facingDirection == true)
    {
        DrawTexture(this->texture2, this->position.x, this->position.y, WHITE);
    }

    else
    {
        DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
    }
    
}

Rectangle player::getCollision()
{
    return {this->position.x,this->position.y, 128, 128};
}
