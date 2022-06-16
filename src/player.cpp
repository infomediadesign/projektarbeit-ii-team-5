#include "player.h"
#include "map.h"
#include <iostream>

player::player(map* current_map) : current_map(current_map)
{
    this->image = LoadImage("assets/graphics/Sprites/Character/MainCharacter/Player_Front.png");
    ImageResizeNN(&this->image, this->image.width * scale_factor, this->image.height * scale_factor);
	this->texture = LoadTextureFromImage(this->image); //walking down

    this->image2 = LoadImage("assets/graphics/Sprites/Character/MainCharacter/Player_Back.png");
    ImageResizeNN(&this->image2, this->image2.width * scale_factor, this->image2.height * scale_factor);
    this->texture2 = LoadTextureFromImage(this->image2); //walking up

    this->movement_img = LoadImage("assets/graphics/Sprites/Character/MainCharacter/walkCycle_Blaize.png");
    ImageResizeNN(&this->movement_img, this->movement_img.width * scale_factor, this->movement_img.height * scale_factor);
    this->movement_texture = LoadTextureFromImage(this->movement_img); //walking up

	//this->position.x = Game::ScreenWidth / 2 - this->texture.width / 2;
    this->position.x = current_map->player_start_pos.x - 80;
    this->position.y = current_map->player_start_pos.y- 1700;

}

player::~player()
{
	UnloadTexture(this->texture);
}

void player::update(controlInput controlInputs,std::vector<Rectangle> walls)
{
    //walking animation setup
    this->frames_counter++;

    if (this->frames_counter >= (60 / 8))
    {
        this->frames_counter = 0;
        this->current_frame++;

        if (this->current_frame > 7) this->current_frame = 0;

        this->frame_rec.x = (float)this->current_frame * (float)this->movement_img.width / 8;
    }


    //movement
    // 
    //press W A S D to move
    //stop at borders
    // 
    //right
    if (controlInputs.right && this->position.x <= player::current_map->texture.width - this->texture.width)
    {
        this->position.x += this->movement_speed;
    }
    //left
    //else 
    if (controlInputs.left && this->position.x >= 0)
    {
        this->position.x -= this->movement_speed;
    }
    //up
    //else 
    if (controlInputs.up && this->position.y >= 0)
    {
        this->position.y -= this->movement_speed;
        this->facingDirection = true;
    }
    //down
    //else
    if (controlInputs.down && this->position.y <= player::current_map->texture.height - this->texture.height)
    {
        this->position.y += this->movement_speed;
        this->facingDirection = false;
    }
    //Whenever a collision is found the player will be pushed slightly back into the world until they are out of collisons
    while (checkForAnyCollisions(walls))
    {
        if (controlInputs.left){
            this->position.x += 1.0;
    }
        if (controlInputs.right) {
            this->position.x -= 1.0;
        }
        if (controlInputs.up) {
            this->position.y += 1.0;
        }
        if (controlInputs.down) {
            this->position.y -= 1.0;
        }
    }
}

void player::draw()
{
    if (this->facingDirection == false)
    {
        
        //DrawTextureRec(this->movement_texture, this->frame_rec, position, WHITE);  // Draw part of the texture
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

bool player::checkForAnyCollisions(std::vector<Rectangle> walls)
{
    for (int i = 0; i < walls.size(); i++) {
        if (CheckCollisionRecs(this->getCollision(), walls[i])) {
            std::cout << "wall has been found";
            return true;
        }
        
    }
    return false;
}

Rectangle player::getCollision()
{
    return {this->position.x + 6 * 4,this->position.y + 4 * 4, 20*4, 24*4};
}
