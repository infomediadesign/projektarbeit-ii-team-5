#pragma once

#include <raylib.h>

#include "scene.h"
#include "sprite.h"

namespace game::core {
    /**
     * @brief A central place for graphics and rendering oriented functions
     */
    class Renderer final {
    public:
        /**
        * @brief Draw a sprite to the screen. Oriented to the size, position and rotation angle of the sprite object.
         * The method draws the texture of the sprite in any case - even if its visibility attribute is set to false.
        * @param sprite Sprite object to be drawn.
        */
        static void DrawTexture(const std::shared_ptr<game::core::Sprite> &sprite);
    };
}
