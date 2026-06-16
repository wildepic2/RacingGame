//
// Created by wildepic on 15/06/2026.
//

#include "raylib.h"
#include "playerCarManager.h"

#include "initTextures.h"
#define speed 10.00f

//Draws the player Car
void drawPlayerCar(Vector2 pos , float rotation) {
    DrawTextureEx(textures[0], pos, rotation, 1,WHITE);
}


void playerInput(Vector2 *pos) {
    if (IsKeyDown(KEY_A)) {
        pos->x -= speed;
    }
    else if (IsKeyDown(KEY_D)) {
        pos->x += speed;
    }

    if (IsKeyDown(KEY_W)) {
        pos->y -= speed;
    }
    else if (IsKeyDown(KEY_S)) {
        pos->y += speed;
    }
}
//ALl functions for Player Car
void playerCar(Vector2 *pos , float *rotation) {
    drawPlayerCar(*pos, *rotation);
    playerInput(pos);
}
