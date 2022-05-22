#include "player.h"
#include "map.h"

player::player(map* current_map) : current_map(current_map)
{
    this->image = LoadImage("assets/graphics/Sprites/Character/MainCharacter/player_test.png");
    ImageResizeNN(&this->image, this->image.width * scale_factor, this->image.height * scale_factor);
	this->texture = LoadTextureFromImage(this->image);

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
    }
    //down
    //else
    if (IsKeyDown(KEY_S) && this->position.y <= player::current_map->texture.height - this->texture.height)
    {
        this->position.y += this->movement_speed;
    }

    //dioganal normal speed - not working yet
    /*
    //dioganal line up right
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->position.x += this->movement_speed/2;
        this->position.y -= this->movement_speed/2;
    }
    //dioganal line up left
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
    {
        this->position.x -= this->movement_speed/2;
        this->position.y -= this->movement_speed/2;
    }
    //dioganal down right
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->position.x += this->movement_speed/2;
        this->position.y += this->movement_speed/2;
    }
    //diogonal down left
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        this->position.x -= this->movement_speed/2;
        this->position.y += this->movement_speed/2;
    }
    */
}

void player::draw()
{
    DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
}