//
// Created by Lee on 29.08.2022.
//

#include "itemMudbomb.h"

itemMudbomb::itemMudbomb()
{
    this->name = "Mudbomb";
    this->description = "Macht Schaden.";
    this->texture_item = LoadTexture("assets/graphics/Items/Mudbomb.png");
    this->texture_infos = LoadTexture("assets/graphics/Items/Mudbomb.png");
}