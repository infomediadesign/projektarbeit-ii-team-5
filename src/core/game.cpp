#include <raylib.h>

#include "game.h"

#include "store.h"
#include "stage.h"

using namespace std::string_literals;

game::core::Game::Game(int stage_width, int stage_height, bool full_screen, int target_fps, int window_flags,
                       int exit_key, bool mouse, bool audio, const char *project_name)
                       : stage_width_(stage_width), stage_height_(stage_height), audio_(audio), mouse_(mouse) {
    SetConfigFlags(window_flags);
    InitWindow(stage_width, stage_height, project_name);
    SetWindowMinSize(stage_width / 2, stage_height / 2);
    SetTargetFPS(target_fps);

    // Render texture initialization, used to hold the rendering result, so we can easily resize it
    this->render_target_ = LoadRenderTexture(this->stage_width_, this->stage_height_);
    // Set texture scale filter to use
    SetTextureFilter(this->render_target_.texture, TEXTURE_FILTER_BILINEAR);

    SetExitKey(exit_key);

    if (full_screen)
        ToggleFullscreen();

    if (audio)
        InitAudioDevice();

    if (!mouse)
        HideCursor();
}

game::core::Game::~Game() {
    TraceLog(LOG_INFO, "game::core::Game destructor called");

    // Release the stage object to trigger potential cleanups that may be dependent on code after the Run() function call.
    game::core::Store::stage = nullptr;

    if (this->audio_)
        CloseAudioDevice();

    // Unload render texture
    UnloadRenderTexture(this->render_target_);

    // Close window and OpenGL context
    CloseWindow();
}

void game::core::Game::Run(const std::string& scene_name, std::unique_ptr<game::core::Scene> scene) const {
    // Create game::Stage instance and assign new scene
    game::core::Store::stage = std::make_unique<game::core::Stage>(scene_name, std::move(scene));

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button if defined
    {
        if(this->mouse_)
            this->UpdateMousePosition();

        // Process input and update current active scene
        game::core::Store::stage->Update();

        // Draw
        BeginDrawing();
        ClearBackground(BLACK); // Letterbox color

        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(this->render_target_);
        // Draw the current active scene to render texture
        game::core::Store::stage->Draw();
        EndTextureMode();

        // Draw render texture to window, properly scaled
        this->DrawRenderTexture();
        EndDrawing();

        // Increment game tick counter
        game::core::Store::ticks++;
    } // Main game loop end
}

Vector2 game::core::Game::ClampValue(Vector2 value, Vector2 MIN, Vector2 MAX) {
    Vector2 result = value;

    result.x = (result.x > MAX.x) ? MAX.x : result.x;
    result.x = (result.x < MIN.x) ? MIN.x : result.x;
    result.y = (result.y > MAX.y) ? MAX.y : result.y;
    result.y = (result.y < MIN.y) ? MIN.y : result.y;

    return result;
}

void game::core::Game::UpdateMousePosition() const {
    // Compute required framebuffer scaling
    float scale = MIN((float) GetScreenWidth() / this->stage_width_, (float) GetScreenHeight() / this->stage_height_);

    // Update virtual mouse (clamped mouse value behind game screen)
    Vector2 mouse = GetMousePosition();
    Store::mouse_position.x = (mouse.x - (static_cast<float>(GetScreenWidth()) - (static_cast<float>(this->stage_width_) * scale)) * 0.5f) / scale;
    Store::mouse_position.y = (mouse.y - (static_cast<float>(GetScreenHeight()) - (static_cast<float>(this->stage_height_) * scale)) * 0.5f) / scale;
    Store::mouse_position = ClampValue(Store::mouse_position, {0, 0}, {static_cast<float>(this->stage_width_), static_cast<float>(this->stage_height_)});
}

void game::core::Game::DrawRenderTexture() const {
    // Compute required framebuffer scaling
    float scale = MIN((float) GetScreenWidth() / this->stage_width_, (float) GetScreenHeight() / this->stage_height_);

    // Draw RenderTexture2D to window, properly scaled
    DrawTexturePro(this->render_target_.texture,
                   {0.0f, 0.0f, static_cast<float>(this->render_target_.texture.width), static_cast<float>(-this->render_target_.texture.height)},
                   {(static_cast<float>(GetScreenWidth()) - (static_cast<float>(this->stage_width_) * scale)) * 0.5f,
                    (static_cast<float>(GetScreenHeight()) - (static_cast<float>(this->stage_height_) * scale)) * 0.5f,
                    static_cast<float>(this->stage_width_) * scale, static_cast<float>(this->stage_height_) * scale},
                   {0.0f, 0.0f}, 0.0f, WHITE
    );
}
