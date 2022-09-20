//
// Created by Lee on 29.08.2022.
//

#include "itemSeifenblase.h"

itemSeifenblase::itemSeifenblase(Vector2 pos)
{
    this->name = "Seifenblase";
    this->description = "Idk sieht hübsch aus.";
    this->texture_item = LoadTexture("assets/graphics/Items/Seifenblase.png");
    //this->texture_infos = LoadTexture("");
    this->position = pos;
    this->hitbox_size = 100;
}

























