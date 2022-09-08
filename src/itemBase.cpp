//
// Created by Lee on 08.09.2022.
//

#include "itemBase.h"


void itemBase::update(Vector2 playerPosition)
{
    if (Vector2Distance(playerPosition, this->position) < hitbox_size && is_active == true)
    {
        is_active = false;
    }

    if (IsKeyDown(KEY_H))
    {
        is_hitbox_visible = true;
    }
    else
    {
        is_hitbox_visible = false;
    }
}

void itemBase::draw()
{
    if (is_active == true)
    {
        DrawTexturePro(texture_item,
                       {0, 0, (float)texture_item.width, (float)texture_item.height},
                       {position.x, position.y, (float)texture_item.width * 4, (float)texture_item.height * 4},
                       {0, 0}, 0, WHITE);
    }

    if (is_hitbox_visible && is_active)
    {
        DrawCircle(position.x + texture_item.width*2, position.y + texture_item.width*2, hitbox_size, PINK);
    }
}


Texture2D itemBase::GetTexture() { return texture_item; }
Texture2D itemBase::GetInfos() {return texture_infos; }
std::string itemBase::GetName() { return name; }
std::string itemBase::GetDescription() {return description; }
bool itemBase::GetActive() { return is_active; }
void itemBase::SetCollected(bool status) { is_collected = status; }
bool itemBase::GetCollected() { return is_collected; }