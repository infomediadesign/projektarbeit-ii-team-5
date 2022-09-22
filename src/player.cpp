#include "player.h"
#include "map.h"
#include <iostream>

player::player(map *current_map) : current_map(current_map) {
    this->position.x = current_map->player_start_pos.x;
    this->position.y = current_map->player_start_pos.y;


    this->textureAnimated = LoadTexture("assets/graphics/Sprites/Character/Player/Blaize_Walkcycle_01.png");
}

player::~player() {
    UnloadTexture(this->texture);
}

void player::update(controlInput controlInputs, std::vector<Rectangle> &walls) {
    movement(walls);

    if (IsKeyPressed(KEY_J)) {

    } else if (IsKeyPressed(KEY_K)) {
        inventory_pointer->addMudbomb();
    } else if (IsKeyPressed(KEY_L)) {
        inventory_pointer->addSeifenblase();
    }
}

void player::draw() {
    this->drawActor(this->textureAnimated, this->position);
}

bool player::checkForAnyCollisions(std::vector<Rectangle> walls, int direction) {
    Rectangle playerCollision = this->getCollision(direction);
    for (int i = 0; i < walls.size(); i++) {
        if (CheckCollisionRecs(playerCollision, walls[i])) {
            return true;
        }

    }
    return false;
}

Rectangle player::getCollision(int direction) {
    const float margin = 24;
    const float blockLengthMargin = 15;
    const float blockThickness = 25;
    const float blockLength = 50;
    const float totalSize = blockLength + blockLengthMargin + blockLengthMargin;
    switch (direction) {
        case 0:
            return {this->position.x + margin + blockLengthMargin,
                    this->position.y + margin,
                    blockLength,
                    blockThickness};
            break;
        case 1:
            return {this->position.x + margin,
                    this->position.y + margin+blockLengthMargin,
                    blockThickness,
                    blockLength};
            break;
        case 2:
            return {this->position.x + margin + blockLengthMargin,
                    this->position.y + margin + totalSize - blockThickness,
                    blockLength,
                    blockThickness};
            break;
        case 3:
            return {this->position.x + margin + totalSize - blockThickness,
                    this->position.y + margin + blockLengthMargin,
                    blockThickness,
                    blockLength};
            break;
        default:
            std::cout << "function \"Rectangle player::getCollision(int direction)\" has been called with false parameters!\n";
            return {};
            break;
    }
}

void player::movement(std::vector<Rectangle> &walls) {

    //walking animation setup
    this->frames_counter++;

    if (this->frames_counter >= (60 / 8)) {
        this->frames_counter = 0;
        this->current_frame++;

        if (this->current_frame > 7) this->current_frame = 0;

        this->frame_rec.x = (float) this->current_frame * (float) this->movement_img.width / 8;
    }


    //movement
    //
    //press W A S D to move
    //stop at borders

    // set moving false every frame
    this->isMoving = false;
    if (IsKeyDown(KEY_LEFT_SHIFT)){
        this->movement_speed = 9;
        if (IsKeyDown(KEY_RIGHT_SHIFT)){
            this->movement_speed = 14;
        }
    }
    else{
        this->movement_speed = 5;
    }
    //right
    if (controlInputs->right) {
        this->position.x += this->movement_speed;
        this->facingDirection = right; // enum
        this->isMoving = true;
    }
    //left
    //else
    if (controlInputs->left) {
        this->position.x -= this->movement_speed;
        this->facingDirection = left; // enum
        this->isMoving = true;
    }
    //up
    //else
    if (controlInputs->up) {
        this->position.y -= this->movement_speed;
        this->facingDirection = up; // enum
        this->isMoving = true;
    }
    //down
    if (controlInputs->down) {
        this->position.y += this->movement_speed;
        this->facingDirection = down; // enum
        this->isMoving = true;
    }
    const float pushoutStrength = 1;
    //Whenever a collision is found the player will be pushed slightly back into the world until they are out of collisons
    for (int i = 0; i < 4; ++i) {
        while (checkForAnyCollisions(walls, i)) {
            switch (i) {
                case 0:
                    this->position.y += pushoutStrength;
                    break;
                case 1:
                    this->position.x += pushoutStrength;
                    break;
                case 2:
                    this->position.y -= pushoutStrength;
                    break;
                case 3:
                    this->position.x -= pushoutStrength;
                    break;
            }
        }
    }


}
