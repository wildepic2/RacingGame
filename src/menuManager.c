//
// Created by wildepic on 15/06/2026.
//

#include "menuManager.h"

#include "initTextures.h"
#include "raylib.h"
#include "state.h"

void displayMainMenu() {
    //Grass on Startmenu
    DrawTexture(textures[0], 0, 0, WHITE);
    DrawTexture(textures[0], 0, 382, WHITE);
    DrawTexture(textures[0], 0, 420, WHITE);
    DrawTexture(textures[0], 500, 0, WHITE);
    DrawTexture(textures[0], 500, 382, WHITE);
    DrawTexture(textures[0], 500, 420, WHITE);

    //Road on Startmenu
    DrawTexture(textures[1], 206, 0, WHITE);
    DrawTexture(textures[1], 206, 384, WHITE);
    DrawTexture(textures[1], 206, 500, WHITE);

    //Title
    DrawText("Racing Game", 100, 0, 100, BLACK);

    //Draw Car
    DrawTexture(textures[11], 350, 320, WHITE);

    //Draw Controlls
    DrawText("W", 382, 280, 40,DARKBLUE);
    DrawText("A", 300, 400, 40, DARKBLUE);
    DrawText("D", 470, 400, 40,DARKBLUE);
    DrawText("S", 385, 510, 40,DARKBLUE);
    DrawText("SPACE TO BRAKE", 220, 630, 40,BLACK);

    //KeyCombo Activate DEV mode
    if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)) {
        isDev = true;
    }

    //If you press any of controll keys the game starts
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) {
        gameState = PLAYING;
    }
}

void displayGameoverMenu() {
}
