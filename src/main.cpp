#include <cstdlib>
#pragma once
#include "raylib.h"
#include "config.h"

#include "raymath.h"

#include "forestSpiritsStructs.h"

#include "sprite.h"
#include "player.h"
#include "map.h"
#include "inventory.h"
#include "screenDeath.h"
#include <iostream>




//initialization within main()
int main() {
	// Raylib initialization
	// Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
	InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
	SetTargetFPS(60);


	// initialize enum for screens
	typedef enum GameScreen { HOME = 0, GAMEPLAY, FIGHT, DEATH } Gamescreen; //LOGO = 0


#ifdef GAME_START_FULLSCREEN
	ToggleFullscreen();
#endif

	// Your own initialization code here
	controlInput controlInputs{};

	Camera2D* this_camera = new Camera2D;
	map* this_map = new map;
	player* this_player = new player(this_map);
	inventory* this_inventory = new inventory(&controlInputs);
    screenDeath* screen_death = new screenDeath();
    screen_death->controlInputs = &controlInputs;

	this_camera->target = this_player->position;
	this_camera->offset = Vector2{ Game::ScreenWidth / 2.0f - this_player->texture.width / 2, Game::ScreenHeight / 2.0f - this_player->texture.height / 2 };
	this_camera->zoom = 1.0f;
	this_camera->rotation = 0.0f;

	Image img_fightScreen = LoadImage("assets/graphics/UI/Fightscreen/Fightscreen_scaled_down_Enemies.png");
	ImageResizeNN(&img_fightScreen, img_fightScreen.width * 4, img_fightScreen.height * 4);
	Texture2D fightScreen = LoadTextureFromImage(img_fightScreen);

	Texture2D homeScreen = LoadTexture("assets/graphics/UI/MenuScreens/Homescreen_WIP.png");
	Texture2D homScreen = LoadTexture("assets/graphics/UI/MenuScreens/Homscreen_WIP.png");

	Texture2D borderLeft = LoadTexture("assets/graphics/UI/LeftBorder.png");
	Texture2D borderRight = LoadTexture("assets/graphics/UI/RightBorder.png");


	int framesCounter = 0;

	// sets default to screen whith which the game shall start when being executed
	GameScreen currentScreen = HOME; //LOGO

	// Frames Per Second are kept to 60 frames per second
	SetTargetFPS(60);



	//void UpdateCameraCenter(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);


	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Updates that are made by frame are coded here

		//which screen is currently used
		//switch between frames by events
		updateControls(&controlInputs);

		switch (currentScreen) {

		case HOME:
		{
            // reset player position everytime when home screen opens
            //this_player->position = this_map->player_start_pos;

			// Press enter to change to GAMEPLAY screen
			if (controlInputs.confirm == 1)
			{
				currentScreen = GAMEPLAY;

			}
		} break;

		case GAMEPLAY:
		{
			// Press enter to change to ENDING screen
			if (controlInputs.confirm == 1) // || this_player->position.x < 15 * 32 && this_player->position.x > 14 * 32 && this_player->position.y < 9 * 32 && this_player->position.y > 8 * 32)
			{
				currentScreen = FIGHT;
			}

			if (IsKeyPressed(KEY_T))
			{
				currentScreen = HOME;
			}

			//player cant move while inventory open

			if (!this_inventory->visible)
			{

				this_player->update(controlInputs, this_map->collisionRectangles);
				this_camera->target = this_player->position;

			}

			this_inventory->update();
		} break;

		case FIGHT:
		{

			// Press enter to return to TITLE screen
			if (controlInputs.confirm == 1)
			{
				currentScreen = GAMEPLAY;
			}

			//press space to death screen
			if (IsKeyPressed(KEY_SPACE))
			{
				currentScreen = DEATH;
			}

		} break;

		case DEATH:
		{
            // reset player position to begin of map
            this_player->position = this_map->player_start_pos;

            screen_death->update();
            if (screen_death->buttons == screenDeath::giveUp && controlInputs.confirm == 1)
            {
                currentScreen = HOME;
            }
            else if (screen_death->buttons == screenDeath::tryAgain && controlInputs.confirm == 1)
            {
                currentScreen = GAMEPLAY;
            }


		} break;

		}




		BeginDrawing();
		// You can draw on the screen between BeginDrawing() and EndDrawing()
		// ...
		// ...

		ClearBackground(WHITE);

		switch (currentScreen)
		{
		case HOME:
		{
			//Draw TITLE screen here!
			DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, GREEN);
			DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
			DrawText("PRESS ENTER to JUMP to GAMEPLAY SCREEN", 240, 500, 20, DARKGREEN);
			if (IsKeyUp(KEY_G)) {
				DrawTexturePro(homeScreen, { 0,0,(float)homeScreen.width,(float)homeScreen.height }, { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() }, {}, {}, WHITE);
			}
			else
				DrawTexturePro(homScreen, { 0,0,(float)homScreen.width,(float)homScreen.height }, { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() }, {}, {}, WHITE);
		} break;
		case GAMEPLAY:
		{
			//Draw Game Screen here
			//order equals order of layers

			ClearBackground(BROWN);



			BeginMode2D(*this_camera);
			//Here the Camera can be controlled with Help of the right stick.
			this_camera->offset = Vector2{ GetScreenWidth() / 2.0f - 32, GetScreenHeight() / 2.0f - 32 };
			this_camera->offset.x -= 128 * GetGamepadAxisMovement(0, 2);
			this_camera->offset.y -= 128 * GetGamepadAxisMovement(0, 3);
			this_map->drawBackground();
			this_player->draw();
			this_map->drawForeground();
			if (IsKeyDown(KEY_H))
			{
				this_map->drawCollision();
			}
			EndMode2D();

			this_inventory->draw();
			DrawOrnaments(borderLeft, borderRight);

		} break;
		case FIGHT:
		{
			// TODO: Draw ENDING screen here!
			DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, RED);
			DrawText("ENDING SCREEN", 20, 20, 40, BLACK);
			DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 240, 500, 20, BLACK);

			DrawTexture(fightScreen, 0, 0, WHITE);
		} break;
		case DEATH:
		{
            screen_death->draw();
		} break;
		default: break;
		}

		EndDrawing();
	} // Main game loop end

	// De-initialization here
	// ...
	// ...
	this_player->~player();
	this_map->~map();
	this_inventory->~inventory();
    screen_death->~screenDeath();
	// Close window and OpenGL context
	CloseWindow();

	return EXIT_SUCCESS;
}


void updateControls(controlInput* x) {
	float deadzone = 0.65;
	//Upwards
	if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || (GetGamepadAxisMovement(0, 1) < -deadzone))
		x->up++;
	else
		x->up = 0;
	//Downwards
	if (IsKeyDown(KEY_S) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || (GetGamepadAxisMovement(0, 1) > deadzone))
		x->down++;
	else
		x->down = 0;
	//Leftwards
	if (IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || (GetGamepadAxisMovement(0, 0) < -deadzone))
		x->left++;
	else
		x->left = 0;
	//Rightwards
	if (IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || (GetGamepadAxisMovement(0, 0) > deadzone))
		x->right++;
	else
		x->right = 0;
	//Confirmwards
	if (IsKeyDown(KEY_ENTER) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
		x->confirm++;
	else
		x->confirm = 0;
	//Cancelwards
	if (IsKeyDown(KEY_RIGHT_SHIFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
		x->cancel++;
	else
		x->cancel = 0;
	//First option, Apostrophe equals "Ä"
	if (IsKeyDown(KEY_APOSTROPHE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) || IsKeyDown(KEY_I))
		x->opt1++;
	else
		x->opt1 = 0;
	//Second option, Slash equals "-"
	if (IsKeyDown(KEY_SLASH) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_UP))
		x->opt2++;
	else
		x->opt2 = 0;

}

void SmartToggleFullscreen(Camera2D* cam) {
	if (IsWindowFullscreen()) {
        SetWindowSize(1280, 960);
		ToggleFullscreen();
		cam->zoom = 1.0;


		
	}
	else {
		cam->zoom = (float)GetMonitorHeight(0) / 960.0f;
		SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
		ToggleFullscreen();
	}
	return;
}

void DrawOrnaments(Texture& borderLeft, Texture& borderRight) {
	float scalefactor = ((float)GetScreenHeight() / (float)borderLeft.height) * ((float)GetMonitorHeight(0) / 960.0f);
	float coverspace = (float)(GetScreenWidth() - 1280.0f) / 2;
	DrawTexturePro(
		borderLeft,
		{0,0,(float)borderLeft.width,(float)borderLeft.height},
		{coverspace-(borderLeft.width*scalefactor), 0, borderLeft.width*scalefactor, borderLeft.height*scalefactor},
		{},0,WHITE
	);
	DrawTexturePro(
		borderRight,
		{ 0,0,(float)borderRight.width,(float)borderRight.height },
		{ GetScreenWidth()-coverspace, 0, borderRight.width * scalefactor, borderRight.height * scalefactor},
		{}, 0, WHITE
	);
};