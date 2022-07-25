//
// Created by Lee on 25.07.2022.
//

#include "screenDeath.h"

screenDeath::screenDeath()
{
    this->screen = LoadTexture("assets/graphics/UI/MenuScreens/DeathScreen.png");
    this->button_giveup = LoadTexture("assets/graphics/UI/MenuScreens/DeathScreen_GiveUp.png");
    this->button_tryAgain = LoadTexture("assets/graphics/UI/MenuScreens/DeathScreen_TryAgain.png");
    // button is per default give up
    this->buttons = giveUp;
    this->button_current = button_giveup;
}

void screenDeath::update()
{
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S))
    {
        switch (this->buttons)
        {
            case giveUp:
                button_current = button_tryAgain;
                buttons = tryAgain;
                break;

            case tryAgain:
                button_current = button_giveup;
                buttons = giveUp;
                break;
        }
    }
}

int screenDeath::returnButton()
{
    return buttons;
}

void screenDeath::draw()
{
    DrawTexturePro(this->screen, { 0,0,(float)this->screen.width,(float)this->screen.height }, { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() }, {}, 0.0, WHITE);
    DrawTexturePro(this->button_current, { 0,0,(float)this->button_current.width,(float)this->button_current.height }, { 0,0,(float)GetScreenWidth(),(float)GetScreenHeight() }, {}, 0.0, WHITE);

}

screenDeath::~screenDeath()
{
    UnloadTexture(this->screen);
    UnloadTexture(this->button_giveup);
    UnloadTexture(this->button_tryAgain);
}