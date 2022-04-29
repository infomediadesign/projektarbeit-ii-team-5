#pragma once

#include <string>

#include "scene.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

namespace game::core {
    /**
     * @brief The entry point into the game. The constructor is used to specify the basic settings such as the size of
     * the drawing area in pixels. Finally, a first game scene can be started via the Run() method.
     */
    class Game final {
    public:
        Game() = delete;

        /**
         * Create a new Game instance
         * @brief Constructor.
         * @param stage_width Width of the game scene (unscaled). Fixed for the entire run time of the game.
         * @param stage_height Height of the game scene (unscaled). Fixed for the entire run time of the game.
         * @param full_screen Start in full screen or window mode.
         * @param target_fps Target fps, usually 60 fps.
         * @param window_flags Raylib window flags, preffered: GAME_CONFIG_FLAGS FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT
         * @param exit_key Game exit key. E.g. KEY_ESCAPE. Set it to KEY_NULL if the game app should not stop directly by pressing a key.
         * @param mouse If true, the mouse position is available in game::core::Store::mouse_position. Please do not use the Raylib function GetMousePosition()  which will not wok because of the scaling and letterboxing system.
         * @param audio If true, Raylib will initialize the audio device.
         * @param project_name Project name to be displayed as window title in Window mode.
         */
        Game(int stage_width, int stage_height, bool full_screen, int target_fps, int window_flags, int exit_key,
             bool mouse, bool audio, const char *project_name);

        Game(const game::core::Game &game) = delete;

        Game &operator=(const Game &) = delete;

        ~Game();

        /**
         * The method creates the main stage object of the game, which is accessible under game::core::Store::stage and
         * transfers the scene object to the stage.
         *
         * The method also implements the main game loop. In this, the contents of the current game scene are drawn via
         * the stage object game::core::Store::stage.
         *
         * Furthermore, the method increments the global game counter game::core::Store::ticks and updates the
         * mouse pointer coordinates in game::core::Store::mouse_position if mouse support was enabled when
         * instantiating the game object.
         *
         * The method is also responsible for correctly scaling the displayed scene and inserting letterboxes if
         * necessary to preserve the aspect ratio.
         *
         * @brief Starts the first game scene.
         */
        void Run(const std::string &scene_name, std::unique_ptr<game::core::Scene> scene) const;

    private:
        /// Width of the game scene (unscaled). Fixed for the entire run time of the game.
        int stage_width_;
        /// Height of the game scene (unscaled). Fixed for the entire run time of the game.
        int stage_height_;
        /// Defines whether the audio device is initialized.
        bool audio_;
        /// Defines if the mouse support should be activated.
        bool mouse_;

        /// Temporary render target, which will later be output correctly scaled on the screen.
        RenderTexture2D render_target_ = { };

        /**
         * @brief Clamp Vector2 value with MIN and MAX and return a new vector2. Required for virtual mouse, to clamp
         * inside virtual game size
         */
        [[nodiscard]] static Vector2 ClampValue(Vector2 value, Vector2 MIN, Vector2 MAX);

        /**
         * @brief Update virtual mouse position. This becomes necessary because the Raylib function GetMousePosition
         * can no longer work correctly due to the scaling of the graphics output.
         */
        void UpdateMousePosition() const;

        /**
         * @brief Draws the correctly scaled and, if necessary, letterboxed graphic on the screen
         */
        void DrawRenderTexture() const;
    };
}