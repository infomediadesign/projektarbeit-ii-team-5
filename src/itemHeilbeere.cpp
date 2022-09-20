//
// Created by Lee on 29.08.2022.
//

#include "itemHeilbeere.h"

itemHeilbeere::itemHeilbeere(Vector2 pos)
{
    this->name = "Heilbeere";
    this->description = "Heilt HP.";
    this->healHP = 100;
    this->texture_item = LoadTexture("assets/graphics/Items/Heilbeeren.png");
    this->position = pos;
    this->hitbox_size = 100;
}