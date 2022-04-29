#include <raylib.h>

#include <utility>

#include "store.h"
#include "config.h"

#include "sprite_animated.h"

game::core::SpriteAnimated::SpriteAnimated(std::shared_ptr<game::core::Texture2D> texture, float frame_width, float frame_height, int row, int steps, int speed)
        : SpriteAnimated(std::move(texture), frame_width, frame_height, row, steps, speed, 0, 0, 0.0) {
}

game::core::SpriteAnimated::SpriteAnimated(std::shared_ptr<game::core::Texture2D> texture, float frame_width, float frame_height, int row, int steps, int speed, int pos_x, int pos_y)
        : SpriteAnimated(std::move(texture), frame_width, frame_height, row, steps, speed, pos_x, pos_y, 0.0) {
}

game::core::SpriteAnimated::SpriteAnimated(std::shared_ptr<game::core::Texture2D> texture, float frame_width, float frame_height, int row, int steps, int speed, int pos_x, int pos_y, float rotation)
        : game::core::Sprite(std::move(texture), pos_x, pos_y, {frame_width/2, frame_height/2}, rotation, {0, static_cast<float>(row - 1) * frame_height, frame_width, frame_height}) {
    this->states_.push_back({row, steps, speed, frame_width, frame_height});
}

void game::core::SpriteAnimated::Update() {
    if(!visible && !update_if_invisible)
        return;

    if(this->states_[state_].steps <= 1)
        return;

    if (game::core::Store::ticks % this->states_[this->state_].speed == 0) {
        this->current_step_++;

        if (this->current_step_ >= this->states_[this->state_].steps) {
            this->current_step_ = 0;
            this->SwitchState();
        }
        else
            this->frame_.x += this->states_[this->state_].frame_width;
    }
}

void game::core::SpriteAnimated::AddState(int row, int steps, int speed, float frame_width, float frame_height) {
    this->states_.push_back({row, steps, speed, frame_width, frame_height});
}

void game::core::SpriteAnimated::SwitchState() {
    this->state_ = this->next_state_;
    this->frame_ = {0, static_cast<float>(this->states_[this->state_].row - 1) * this->states_[this->state_].frame_height, this->states_[this->state_].frame_width, this->states_[this->state_].frame_height};
}

int game::core::SpriteAnimated::state() const {
    return this->state_;
}

void game::core::SpriteAnimated::nextState(int nextState) {
    this->next_state_ = nextState;
}
