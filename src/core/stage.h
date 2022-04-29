#pragma once

#include <memory>
#include <string>

#include <raylib.h>
#include <map>

#include "scene.h"
#include "sprite.h"

namespace game::core {
    /**
     * A main stage object is created by the Game class instance. This stage object is accessible under game::core::Store::stage.
     *
     * Several scenes can be managed by the stage object. Scenes can be replaced by new scenes and you can switch between existing scenes.
     * The change of scenes can be triggered by the respective scenes themselves.
     *
     * Stage also calls the Update() and Draw() methods of the active scene. Draw functions that are triggered by
     * the scene's Draw() method are always executed after the scene's actors are already drawn to the screen.
     *
     * @brief Stage is used to manage scenes. The Stage automatically draws all Actor objects of a scene if they are set to visible.
     */
    class Stage final {
    public:
        Stage() = delete;

        /**
         * @brief Constructor.
         *
         * Create a new Stage object
         * @param new_scene_name Name of the new scene.
         * @param scene Unique pointer to a new scene object.
         */
        Stage(const std::string& new_scene_name, std::unique_ptr<game::core::Scene> scene);

        Stage(const game::core::Stage &stage) = delete;

        Stage &operator=(const Stage &) = delete;

        virtual ~Stage() = default;

        /**
         * @return Returns a reference to currently active scene.
         */
        [[nodiscard]] const std::shared_ptr<game::core::Scene> &scene() const;

        /**
         * @return Returns a reference to the map containing all managed scenes.
         */
        [[nodiscard]] const std::map<std::string, std::shared_ptr<game::core::Scene>> &scenes() const;

        /**
         * @brief Inserts a new scene into scenes_, sets next_scene_ to the new scene and removes the scene identified by old_scene_name.
         * @param old_scene_name Name of the scene to be removed.
         * @param new_scene_name Name of the new scene to switch to.
         * @param scene Shared pointer to the new scene to switch to.
         */
        void replaceWithNewScene(const std::string& old_scene_name, const std::string& new_scene_name, std::shared_ptr<Scene> scene);

        /**
         * @brief Sets next_scene_ to the existing scene identified by new_scene_name and removes the scene identified by old_scene_name.
         * @param old_scene_name Name of the scene to be removed.
         * @param new_scene_name Name of the existing scene to switch to.
         */
        void replaceWithExistingScene(const std::string& old_scene_name, const std::string& new_scene_name);

        /**
         * @brief Inserts a new scene into scenes_ and sets next_scene_ to the new scene.
         * @param new_scene_name Name of the new scene to switch to.
         * @param scene Shared pointer to the new scene to switch to.
         */
        void switchToNewScene(const std::string& new_scene_name, std::shared_ptr<Scene> scene);

        /**
         * @brief Sets next_scene_ to the scene identified by new_scene_name
         * @param new_scene_name Name of the scene to switch to.
         */
        void switchToScene(const std::string& new_scene_name);

        /**
         * @brief Changes the active scene if next_scene_ is set. Then calls the update() method of the scene.
         */
        void Update();

        /**
         * @brief Draws all visible actors of the active scene. Then calls the Draw() method of the active scene.
         */
        void Draw();

    private:
        /// Active scene object.
        std::shared_ptr<game::core::Scene> scene_;

        /// Pointer to the next scene to be active. The switch will happen when Update() is called the next time.
        std::shared_ptr<game::core::Scene> next_scene_;

        /// This maps stores all referenced scenes. They can be addressed by their names.
        std::map<std::string, std::shared_ptr<game::core::Scene>> scenes_;

    };
}
