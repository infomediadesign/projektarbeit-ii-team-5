#include "renderer.h"

#include "stage.h"

void game::core::Renderer::DrawTexture(const std::shared_ptr<game::core::Sprite>& sprite) {
    DrawTexturePro(sprite->texture(), sprite->frame(),
                   {(static_cast<float>(sprite->pos_x) + sprite->rotation_origin.x), (static_cast<float>(sprite->pos_y) + sprite->rotation_origin.y),
                    static_cast<float>(sprite->frame().width), static_cast<float>(sprite->frame().height)},
                   sprite->rotation_origin, sprite->rotation, sprite->tint);
}
