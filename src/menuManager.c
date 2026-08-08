//
// Created by wildepic on 15/06/2026.
//

#include "menuManager.h"

#include "finishMark.h"
#include "gameOverlayText.h"
#include "initTextures.h"
#include "raylib.h"
#include "state.h"

// Renders the background for menus - draws grass tiles and a car sprite
// Used as a backdrop for both main menu and game over screen
void background() {
    DrawTexture(textures[0], 0, 0, WHITE);
    DrawTexture(textures[0], 0, 382, WHITE);
    DrawTexture(textures[0], 0, 420, WHITE);
    DrawTexture(textures[0], 500, 0, WHITE);
    DrawTexture(textures[0], 500, 382, WHITE);
    DrawTexture(textures[0], 500, 420, WHITE);

    DrawTexture(textures[1], 206, 0, WHITE);
    DrawTexture(textures[1], 206, 384, WHITE);
    DrawTexture(textures[1], 206, 500, WHITE);

    // Draw Car
    DrawTexture(textures[11], 350, 320, WHITE);
}

// Displays the main menu screen with title, controls, and enables dev mode activation
// Dev mode is activated by pressing LEFT and RIGHT arrows simultaneously
// Game starts when player presses any movement key
void displayMainMenu() {
    background();

    // Title
    DrawText("Racing Game", 100, 0, 100, BLACK);

    // Draw Controlls
    DrawText("W", 382, 280, 40, DARKBLUE);
    DrawText("A", 300, 400, 40, DARKBLUE);
    DrawText("D", 470, 400, 40, DARKBLUE);
    DrawText("S", 385, 510, 40, DARKBLUE);
    DrawText("SPACE TO BRAKE", 220, 630, 40, BLACK);

    // KeyCombo Activate DEV mode
    if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)) {
        isDev = true;
    }

    // If you press any of controll keys the game starts
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) {
        gameState = PLAYING;
    }
}

// Displays the game over screen with final time, best time, and play again button
// Button press transitions back to PLAYING state and resets the stopwatch
void displayGameoverMenu() {
    background();

    int minute, sec, ms;
    reconstructTime(&minute, &sec, &ms, stoppWatchTime);

    // Shows Timer
    DrawText(TextFormat("%.2d:%.2d:%.2d", minute, sec, ms), 282, 255, 60, BLACK);
    reconstructTime(&minute, &sec, &ms, highscore);
    if (highscore < 14400000) {
        DrawText(TextFormat("Best: %.2d:%.2d:%.2d", minute, sec, ms), 227, 200, 52, RED);
    }

    DrawRectangle(210, 600, 381, 70, BLACK);
    DrawText("Play Again", 240, 600, 60, WHITE);

    if (GetMouseX() > 210 && GetMouseX() < 591 && GetMouseY() > 600 && GetMouseY() < 670 && IsMouseButtonReleased(0)) {
        gameState = PLAYING;
        stoppWatchTime = 0;
    }
}
