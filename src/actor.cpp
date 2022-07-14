//
// Created by Lee on 14.07.2022.
//
#include "actor.h"

void actor::drawActor(Texture2D texture, Vector2 pos)
{
    this->actor_frames++;
    this->actor_frame_offset = actor_frames / frame_speed % (texture.width/32);

    if (this->isMoving == true)
    {
        DrawTexturePro(texture,
                       {(float)actor_frame_offset * 32, (float)facingDirection * 32, 32, 32},
                       {this->position.x, this->position.y, 128, 128},
                       {},0, WHITE );
    }
    else
    {
        DrawTexturePro(texture,
                       {0,(float)facingDirection*32, 32, 32},
                       {this->position.x, this->position.y, 128, 128},
                       {},0, WHITE );
    }
}