#include <raylib.h>

#include "actor.h"

game::core::Actor::Actor(std::shared_ptr<game::core::Sprite> sprite) : sprite_(std::move(sprite)){
    TraceLog(LOG_INFO, "game::core::Actor constructor called");
}

game::core::Actor::~Actor() {
    TraceLog(LOG_INFO, "game::core::Actor destructor called");
}

const std::shared_ptr<game::core::Sprite> &game::core::Actor::sprite() const {
    return this->sprite_;
}

void game::core::Actor::sprite(std::shared_ptr<game::core::Sprite> sprite) {
    this->sprite_ = std::move(sprite);
}

