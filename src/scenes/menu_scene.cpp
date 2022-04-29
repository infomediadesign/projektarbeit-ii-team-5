#include <string>

#include <raylib-cpp.hpp>
#include <raylib.h>

#include <store.h>

#include "scenes.h"

using namespace std::string_literals;

game::scenes::MenuScene::MenuScene() {
    // Your scene initialization code here...
}

game::scenes::MenuScene::~MenuScene() {
    // Your scene cleanup code here...
}

void game::scenes::MenuScene::Update() {
    // Your process input and update game scene code here...
    if (IsKeyPressed(KEY_ENTER))
        game::core::Store::stage->replaceWithNewScene("menu"s, "game"s, std::make_unique<GameScene>());
}

void game::scenes::MenuScene::Draw() {
    // Your scene drawing code here...
    // Note that scene-actors are drawn automatically
    DrawText("Menu - press ENTER to load game scene", 10, 10, 30, LIGHTGRAY);
}
