﻿#include <cstdlib>
#include "raylib.h"
#include "config.h"

#include "raymath.h"

#include "sprite.h"
#include "player.h"
#include "map.h"
#include "inventory.h"


//initialization within main()
int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    

    typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, FIGHT } Gamescreen;
    

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Camera2D* this_camera = new Camera2D;
    map* this_map = new map;
    player* this_player = new player(this_map);
    inventory* this_inventory = new inventory;
    
    this_camera->target = this_player->position;
    this_camera->offset = Vector2 {Game::ScreenWidth / 2.0f - this_player->texture.width/2, Game::ScreenHeight / 2.0f - this_player->texture.height/2};
    this_camera->zoom = 1.0f;
    this_camera->rotation = 0.0f;

    Image img_fightScreen = LoadImage ("assets/graphics/backgrounds/UI/Fightscreen/Fightscreen_scaled_down.png");
    ImageResizeNN(&img_fightScreen, img_fightScreen.width * 4, img_fightScreen.height * 4);
    Texture2D fightScreen = LoadTextureFromImage(img_fightScreen);


    int framesCounter = 0;
      
    //sets default to screen whith which the game shall start when being executed
    GameScreen currentScreen = LOGO;

    //Frames Per Second are kept to 60 frames per second
    SetTargetFPS(60);



    //void UpdateCameraCenter(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);

    
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here
        // ...
        // ...
        

        switch (currentScreen) {
            
            
            case LOGO:
            {
                //update frames variables here

                framesCounter++;

                //wait 2 seconds (120 frames) before jumping to next frame
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }


            } break;
            case TITLE:
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
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = FIGHT;
                }

                if (IsKeyPressed(KEY_T))
                {
                    currentScreen = TITLE;
                }

                //TODO: wenn camera nicht border berührt
                this_camera->target = this_player->position;
                this_player->update();
                this_inventory->update();

                this_inventory->position.x = this_player->position.x;
                this_inventory->position.y = this_player->position.y;

                //player cant move while inventory open
                /*
                if (!this_inventory->visible)
                {
                    
                   
                }
                */
                
                

            } break;
            case FIGHT:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = GAMEPLAY;
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
                
                case LOGO:
                {
                    //Draw LOGO screen here!
                    DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, LIGHTGRAY);
                    DrawText("LOGO SCREEN", 20, 20, 40, GRAY);
                    DrawText("WAIT for 2 SECONDS...", 370, Game::ScreenHeight /2, 20, GRAY);
                    

                } break;
                
                case TITLE:
                {
                    //Draw TITLE screen here!
                    DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER to JUMP to GAMEPLAY SCREEN", 240, 500, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    //Draw Game Screen here
                    //order equals order of layers

                    DrawRectangle(0, 0, Game::ScreenWidth, Game::ScreenHeight, BROWN);

                    BeginMode2D(*this_camera);
                    DrawTexture(this_map->texture, 0, 0, WHITE);
                    this_player->draw();
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
