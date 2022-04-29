#pragma once

#include "sprite.h"

namespace game::core {
    /**
     * @brief Actor base class. Actors represent all game objects, such as players, enemies and other obstacles.
     *
     * Graphically, actors are represented via a sprite object associated with them. The sprite must be passed in the constructor call.
     *
     * Actors can be placed in the actor-map of a scene object and will be drawn automatically if their visible
     * attribute is true. If actor objects are supposed to be available across scenes, they can be stored in
     * game::core::actors. Objects that are only referenced there will not be drawn automatically.
     * The position and appearance of an actor object in the game depends on attributes (e.g. position and rotation) of its sprite member.
     */
    class Actor {
    private:
        std::shared_ptr<game::core::Sprite> sprite_;

    public:
        Actor() = delete;

        /**
         * @brief Constructor.
         *
         * Create a new Actor object.
         * @param sprite Sprite object that is assigned to the Actor.
         */
        explicit Actor(std::shared_ptr<game::core::Sprite> sprite);

        Actor(const game::core::Actor &actor) = delete;

        Actor &operator=(const Actor &) = delete;

        virtual ~Actor();

        /**
         * @brief Returns the sprite object of the actor
         * @return Shared pointer of the objects Sprite.
         */
        [[nodiscard]] const std::shared_ptr<game::core::Sprite> &sprite() const;

        /**
         * @brief Replaces the current sprite object of the actor.
         */
        void sprite(std::shared_ptr<game::core::Sprite> sprite);
    };
}
