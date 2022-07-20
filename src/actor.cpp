//
// Created by Lee on 14.07.2022.
//
#include "actor.h"

void actor::drawActor(Texture2D& texture, Vector2 pos)
{
    this->actor_frames++;
    this->actor_frame_offset = actor_frames / frame_speed % (texture.width/64);

    if (IsKeyDown(KEY_H)){
        DrawRectangleRec({this->position.x+24,this->position.y+24,80,80},GetColor(0xFF00FFFF));
    }

    if (this->isMoving == true)
    {
        DrawTexturePro(texture,
                       {(float)actor_frame_offset * 64, (float)facingDirection * 64, 64, 64},
                       {this->position.x, this->position.y, 128*2, 128*2},
                       {16*4, 16*4},0, WHITE );
    }
    else
    {
        DrawTexturePro(texture,
                       {0,(float)facingDirection*64, 64, 64},
                       {this->position.x, this->position.y, 256, 256},
                       {64,64},0, WHITE );
    }
}