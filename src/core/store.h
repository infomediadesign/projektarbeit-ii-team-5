#pragma once

#include <map>

#include <raylib.h>

#include "stage.h"
#include "actor.h"

namespace game::core {
    /**
     * @brief A central place to share globally accessible objects that should be accessible from anywhere.
     */
    struct Store final {
        /// The Stage object is responsible for the scene change and for updating and drawing the scene contents
        inline static std::unique_ptr<game::core::Stage> stage = nullptr;

        /// To get the mouse position the mouse support must be enabled when initializing the Game object.
        /// @brief The virtual mouse position.
        inline static Vector2 mouse_position = { };

        /// Global game counter. Can be used e.g. for the calculation of animation times.
        inline static long long int ticks = 1;

        /// The actors map can contain shared pointers to actor objects that are to be used across multiple scenes (e.g. the player actor).
        inline static std::map<std::string, std::shared_ptr<game::core::Actor>> actors = { };
    };
}
