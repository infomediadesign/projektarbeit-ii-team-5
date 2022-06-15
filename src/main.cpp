#include <cstdlib>
#pragma once
#include "raylib.h"
#include "config.h"

#include "raymath.h"

#include "controllInput.h"

#include "sprite.h"
#include "player.h"
#include "map.h"
#include "inventory.h"


controlInput controlInputs{};

//initialization within main()
int main() {
	// Raylib initialization
	// Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
	InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
	SetTargetFPS(60);



	typedef enum GameScreen { HOME = 0, GAMEPLAY, FIGHT, DEATH } Gamescreen; //LOGO = 0


#ifdef GAME_START_FULLSCREEN
	ToggleFullscreen();
#endif

	// Your own initialization code here

	Camera2D* this_camera = new Camera2D;
	map* this_map = new map;
	player* this_player = new player(this_map);
	inventory* this_inventory = new inventory(&controlInputs);

	this_camera->target = this_player->position;
	this_camera->offset = Vector2{ Game::ScreenWidth / 2.0f - this_player->texture.width / 2, Game::ScreenHeight / 2.0f - this_player->texture.height / 2 };
	this_camera->zoom = 1.0f;
	this_camera->rotation = 0.0f;

	Image img_fightScreen = LoadImage("assets/graphics/backgrounds/UI/Fightscreen/Fightscreen_scaled_down_Enemies.png");
	ImageResizeNN(&img_fightScreen, img_fightScreen.width * 4, img_fightScreen.height * 4);
	Texture2D fightScreen = LoadTextureFromImage(img_fightScreen);

	Texture2D homeScreen = LoadTexture("assets/graphics/backgrounds/MenuScreens/Homescreen_WIP.png");
	Texture2D homScreen = LoadTexture("assets/graphics/backgrounds/MenuScreens/Homscreen_WIP.png");
	Texture2D deathScreen = LoadTexture("assets/graphics/backgrounds/MenuScreens/DeathScreen.png");


	int framesCounter = 0;

	//sets default to screen whith which the game shall start when being executed
	GameScreen currentScreen = HOME; //LOGO

	//Frames Per Second are kept to 60 frames per second
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
			// TODO: Update TITLE screen variables here!

			// Press enter to change to GAMEPLAY screen
			if (IsKeyPressed(KEY_ENTER))
			{
				currentScreen = GAMEPLAY;
			}


		} break;
		case GAMEPLAY:
		{
			// Press enter to change to ENDING screen
			if (IsKeyPressed(KEY_ENTER)) // || this_player->position.x < 15 * 32 && this_player->position.x > 14 * 32 && this_player->position.y < 9 * 32 && this_player->position.y > 8 * 32)
			{
				currentScreen = FIGHT;
			}

			if (IsKeyPressed(KEY_T))
			{
				currentScreen = HOME;
			}

			//TODO: wenn camera nicht border berührt


			//player cant move while inventory open

			if (!this_inventory->visible)
			{
				this_camera->target = this_player->position;
				this_player->update();
			}

			this_inventory->update();




		} break;
		case FIGHT:
		{
			// TODO: Update ENDING screen variables here!

			// Press enter to return to TITLE screen
			if (IsKeyPressed(KEY_ENTER))
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
			DrawTexturePro(deathScreen, { 0,0,(float)deathScreen.width,(float)deathScreen.height }, { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() }, {}, 0.0, WHITE);

			if (IsKeyPressed(KEY_ENTER))
			{
				currentScreen = HOME;
			}
		} break;
		default: break;

		}




		BeginDrawing();
		// You can draw on the screen between BeginDrawing() and EndDrawing()
		// ...
		// ...

		ClearBackground(WHITE);

		switch (currentScreen)
		{
			/*
			case LOGO:
			{
				//Draw LOGO screen here!
				DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, LIGHTGRAY);
				DrawText("LOGO SCREEN", 20, 20, 40, GRAY);
				DrawText("WAIT for 2 SECONDS...", 370, Game::ScreenHeight /2, 20, GRAY);


			} break;
			*/
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

			DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, BROWN);



			BeginMode2D(*this_camera);
			//DrawTexture(this_map->texture, 0, 0, WHITE);
			this_map->drawBackground();
			this_player->draw();
			//DrawRectangle(14 * 32, 8 * 32, 32, 32, RED);
			this_map->drawForeground();
			EndMode2D();

			this_inventory->draw();

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
			DrawTexturePro(deathScreen, { 0,0,(float)deathScreen.width,(float)deathScreen.height }, { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() }, {}, 0.0, WHITE);

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

	// Close window and OpenGL context
	CloseWindow();

	return EXIT_SUCCESS;
}


void updateControls(controlInput* x) {
	//Upwards
	if (IsKeyDown(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
		x->up++;
	else
		x->up = 0;
	//Downwards
	if (IsKeyDown(KEY_S) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
		x->down++;
	else
		x->down = 0;
	//Leftwards
	if (IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
		x->left++;
	else
		x->left = 0;
	//Rightwards
	if (IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
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
