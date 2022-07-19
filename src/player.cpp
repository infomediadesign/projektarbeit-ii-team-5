#include "player.h"
#include "map.h"
#include <iostream>

player::player(map* current_map) : current_map(current_map)
{
    this->position.x = current_map->player_start_pos.x - 80;
    this->position.y = current_map->player_start_pos.y- 1700;


    this->textureAnimated = LoadTexture("assets/graphics/Sprites/Character/Player/Blaize_Walkcycle_01.png");
}

player::~player()
{
	UnloadTexture(this->texture);
}

void player::update(controlInput controlInputs,std::vector<Rectangle>& walls)
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

    // set moving false every frame
    this->isMoving = false;

    //right
    if (controlInputs.right && this->position.x <= player::current_map->texture.width - this->texture.width)
    {
        this->position.x += this->movement_speed;
        this->facingDirection = right; // enum
        this->isMoving = true;
    }
    //left
    //else
    if (controlInputs.left && this->position.x >= 0)
    {
        this->position.x -= this->movement_speed;
        this->facingDirection = left; // enum
        this->isMoving = true;
    }
    //up
    //else 
    if (controlInputs.up && this->position.y >= 0)
    {
        this->position.y -= this->movement_speed;
        this->facingDirection = up; // enum
        this->isMoving = true;
    }
    //down
    if (controlInputs.down && this->position.y <= player::current_map->texture.height - this->texture.height)
    {
        this->position.y += this->movement_speed;
        this->facingDirection = down; // enum
        this->isMoving = true;
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
    this->drawActor(this->textureAnimated, this->position);
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
    return {this->position.x + 6 * 4,this->position.y + 6 * 4, 20*4, 20*4};
}
