#pragma once

#include <memory>

#include <actor.h>
#include <scene.h>
#include <sprite.h>
#include <sprite_animated.h>

namespace game::scenes {
    class GameScene final : public game::core::Scene {
    public:
        GameScene();

        ~GameScene() override;

        void Update() override;

        void Draw() override;

    private:
        // Add private members here...
    };
}