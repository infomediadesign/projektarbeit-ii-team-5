//
// Created by Lee on 14.07.2022.
//
#include "actor.h"

void actor::drawActor(Texture2D& texture, Vector2 pos)
{
    // with every loop set actor frames + 1
    this->actor_frames++;

    // frame offset is calculated by current frames of actor and frame speed as well as width of texture
    // so it will switch every few frames to a new frame on the spritesheet
    this->actor_frame_offset = actor_frames / frame_speed % (texture.width/64);


    if (this->isMoving == true)
    {
        // source of where to draw from is actor_frame offset which means in will increase and loop
        // multiplied by facing direction because every direction is another column in the sprite sheet
        DrawTexturePro(texture,
                       {(float)actor_frame_offset * 64, (float)facingDirection * 64, 64, 64},
                       {this->position.x, this->position.y, 128*2, 128*2},
                       {16*4, 16*4},0, WHITE );
    }
    else
    {
        // if its not moving draw the first one in the column to get the facing direction while standing still
        DrawTexturePro(texture,
                       {0,(float)facingDirection*64, 64, 64},
                       {this->position.x, this->position.y, 256, 256},
                       {64,64},0, WHITE );
    }
}