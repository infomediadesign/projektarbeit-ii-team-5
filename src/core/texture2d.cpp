#include <raylib.h>

#include "texture2d.h"

game::core::Texture2D::Texture2D(const char *filename) {
    // @todo Error handling needed
    this->texture_ = LoadTexture(filename);
}

game::core::Texture2D::~Texture2D() {
    TraceLog(LOG_INFO, "game::core::Texture2D destructor called");
    UnloadTexture(this->texture_);
}

const ::Texture2D &game::core::Texture2D::texture() const {
    return this->texture_;
}

const int &game::core::Texture2D::width() const {
    return this->texture_.width;
}

const int &game::core::Texture2D::height() const {
    return this->texture_.height;
}
