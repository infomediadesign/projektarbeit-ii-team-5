//
// Created by Lee on 29.08.2022.
//

#ifndef RAYLIBSTARTER_ITEMBASE_H
#define RAYLIBSTARTER_ITEMBASE_H

#include "string"
#include "raylib.h"

class itemBase {
protected:
    std::string name;
    std::string description;
    Texture2D texture_item;
    Texture2D texture_infos;

public:
    Texture2D GetTexture() { return texture_item; }
    Texture2D GetInfos() {return texture_infos; }
    std::string GetName() { return name; }
    std::string GetDescription() {return description; }

};


#endif //RAYLIBSTARTER_ITEMBASE_H
