//
// Created by Lee on 29.08.2022.
//

#include "itemHeilbeere.h"

itemHeilbeere::itemHeilbeere()
{
    this->name = "Heilbeere";
    this->description = "Heilt HP.";
    this->healHP = 100;
    this->texture_item = LoadTexture("assets/graphics/Items/Heilbeeren.png");
    this->texture_infos = LoadTexture("assets/graphics/Items/Heilbeeren.png");
    this->position = {36 * 4, 531 * 4};
    this->hitbox_size = 50;
}