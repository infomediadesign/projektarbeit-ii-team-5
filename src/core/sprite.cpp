#include <raylib.h>

#include <utility>

#include "sprite.h"

game::core::Sprite::Sprite(std::shared_ptr<game::core::Texture2D> texture)
        : Sprite(std::move(texture), 0, 0, 0.0f) {

}

game::core::Sprite::Sprite(std::shared_ptr<game::core::Texture2D> texture, int pos_x, int pos_y)
        : Sprite(std::move(texture), pos_x, pos_y, 0.0f) {

}

game::core::Sprite::Sprite(std::shared_ptr<game::core::Texture2D> texture, int pos_x, int pos_y, float rotation)
        : texture_(std::move(texture)),
          frame_({0.0, 0.0,
                  static_cast<float>(this->texture_->width()),
                  static_cast<float>(this->texture_->height())}),
          rotation_origin(
                  {static_cast<float>(this->texture_->width()) / 2,
                   static_cast<float>(this->texture_->height()) /2}),
          rotation(rotation),
          pos_x(pos_x),
          pos_y(pos_y) {

}

game::core::Sprite::Sprite(std::shared_ptr<game::core::Texture2D> texture, int pos_x, int pos_y, Vector2 rotation_origin, float rotation, Rectangle frame)
        : texture_(std::move(texture)),
          frame_(frame),
          rotation_origin(rotation_origin),
          rotation(rotation),
          pos_x(pos_x),
          pos_y(pos_y) {

}

game::core::Sprite::~Sprite() {
    TraceLog(LOG_INFO, "game::core::Sprite destructor called");
}

Vector2 game::core::Sprite::position() const {
    return {static_cast<float>(this->pos_x), static_cast<float>(this->pos_y)};
}

[[maybe_unused]] const std::shared_ptr<game::core::Texture2D> &game::core::Sprite::texture_object() const {
    return this->texture_;
}

void game::core::Sprite::texture(const std::shared_ptr<game::core::Texture2D> &texture) {
    this->texture_ = texture;

    this->frame_ = {0.0, 0.0,
                    static_cast<float>(this->texture_->width()),
                    static_cast<float>(this->texture_->height())};

    this->rotation_origin = {static_cast<float>(this->texture_->width()) / 2,static_cast<float>(this->texture_->height()) /2};
}

const ::Texture2D &game::core::Sprite::texture() const {
    return this->texture_->texture();
}

const Rectangle &game::core::Sprite::frame() const {
    return this->frame_;
}

void game::core::Sprite::frame(const Rectangle &frame) {
    this->frame_ = frame;
}
