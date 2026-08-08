//
// Created by wildepic on 8/6/26.
//

#include "countdownGameStart.h"

#include "raylib.h"

int countdown = 5;
int frameCount = 0;

// Displays the countdown timer on screen at the player's position (5, 4, 3, 2, 1, GO)
void showCountdown(Vector2 *pos) {
    if (countdown > 0) {
        DrawText(TextFormat("%d", countdown), (int)pos->x - 0, (int)pos->y - 200, 200, BLACK);
    }
}

// Updates the countdown timer - decrements every 60 frames (approximately 1 second at 60 FPS)
// When countdown reaches 0, the race begins and player input is enabled
void countdownFun() {
    frameCount++;
    if (countdown > 0 && frameCount > 60) {
        countdown--;
        frameCount = 0;
    }
}

// Resets the countdown timer to 5 seconds, used when starting a new game or lap
void resetCountdown() {
    countdown = 5;
}