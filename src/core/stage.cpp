#include <memory>
#include <map>

#include "stage.h"
#include "renderer.h"
#include "sprite.h"

game::core::Stage::Stage(const std::string& new_scene_name, std::unique_ptr<game::core::Scene> scene) {
    this->next_scene_ = std::move(scene);
    this->scenes_.insert(std::make_pair(new_scene_name, this->next_scene_));
}

void game::core::Stage::switchToScene(const std::string& new_scene_name) {
    auto it = this->scenes_.find(new_scene_name);

    if(it != this->scenes_.end())
        this->next_scene_ = it->second;
}

void game::core::Stage::switchToNewScene(const std::string &new_scene_name, std::shared_ptr<Scene> scene) {
    this->next_scene_ = std::move(scene);
    this->scenes_.insert(std::make_pair(new_scene_name, this->next_scene_));
}

void game::core::Stage::replaceWithNewScene(const std::string& old_scene_name, const std::string& new_scene_name, std::shared_ptr<Scene> scene) {
    this->scenes_.erase(old_scene_name);

    this->next_scene_ = std::move(scene);
    this->scenes_.insert(std::make_pair(new_scene_name, this->next_scene_));
}

void game::core::Stage::replaceWithExistingScene(const std::string &old_scene_name, const std::string &new_scene_name) {
    auto it = this->scenes_.find(new_scene_name);

    if(it != this->scenes_.end()) {
        this->scenes_.erase(old_scene_name);
        this->next_scene_ = it->second;
    }
}

const std::shared_ptr<game::core::Scene> &game::core::Stage::scene() const {
    return this->scene_;
}

const std::map<std::string, std::shared_ptr<game::core::Scene>> &game::core::Stage::scenes() const {
    return this->scenes_;
}

void game::core::Stage::Update() {
    if (this->next_scene_) {
        this->scene_ = std::move(this->next_scene_);
    }

    this->scene_->Update();
}

void game::core::Stage::Draw() {
    ClearBackground(WHITE);

    for (auto const& [key, val] : this->scene_->actors) {
        val->sprite()->Update();

        if(val->sprite()->visible)
            game::core::Renderer::DrawTexture(val->sprite());
    }

    this->scene_->Draw();
}
