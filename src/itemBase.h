//
// Created by Lee on 29.08.2022.
//

#ifndef RAYLIBSTARTER_ITEMBASE_H
#define RAYLIBSTARTER_ITEMBASE_H

#include "string"
#include "raylib.h"
#include "raymath.h"

class itemBase {
protected:
    std::string name;
    std::string description;
    Texture2D texture_item;
    Texture2D texture_infos;
    Vector2 position;
    bool is_active = true;
    bool is_collected = false;
    bool is_hitbox_visible = false;
    int hitbox_size = 0;

public:
    Texture2D GetTexture();
    Texture2D GetInfos();
    std::string GetName();
    std::string GetDescription();

    void draw();
    void update(Vector2 playerPosition);
    bool GetActive();
    void SetCollected(bool status);
    bool GetCollected();

};

#endif //RAYLIBSTARTER_ITEMBASE_H
