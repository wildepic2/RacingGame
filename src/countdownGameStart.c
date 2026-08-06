//
// Created by wildepic on 8/6/26.
//

#include "countdownGameStart.h"

#include "raylib.h"

int countdown = 5;
int frameCount = 0;

void showCountdown(Vector2 *pos) {
    if (countdown > 0) {
        DrawText(TextFormat("%d", countdown), pos->x - 0, pos->y - 200, 200, BLACK);
    }
}

void countdownFun() {
    frameCount++;
    if (countdown > 0 && frameCount > 60) {
        countdown--;
        frameCount = 0;
    }
}

void resetCountdown() {
    countdown = 5;
}