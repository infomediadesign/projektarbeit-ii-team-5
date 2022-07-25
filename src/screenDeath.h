//
// Created by Lee on 25.07.2022.
//

#ifndef RAYLIBSTARTER_SCREENDEATH_H
#define RAYLIBSTARTER_SCREENDEATH_H

#include "raylib.h"
#include "forestSpiritsStructs.h"


class screenDeath {
public:
    enum Button {tryAgain = 0, giveUp = 1 };
    Button buttons;

    Texture2D screen;
    Texture2D button_current;
    Texture2D button_giveup;
    Texture2D button_tryAgain;

    controlInput* controlInputs;

    screenDeath();
    ~screenDeath();
    void draw();
    void update();
    int returnButton();

};


#endif //RAYLIBSTARTER_SCREENDEATH_H
