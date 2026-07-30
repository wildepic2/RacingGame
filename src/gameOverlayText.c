//
// Created by wildepic on 30/07/2026.
//

#include "gameOverlayText.h"

#include "raylib.h"
#include "state.h"

void timer() {
    stoppWatchTime+=1;

    int digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0, digit6 = 0;
    digit1 = stoppWatchTime / 100000;
    digit2 = (stoppWatchTime / 10000) % 10;
    digit3 = (stoppWatchTime / 1000) % 10;
    digit4 = (stoppWatchTime / 100) % 10;
    digit5 = (stoppWatchTime / 10) % 10;
    digit6 = stoppWatchTime % 10;

    int minute = digit1 * 10 + digit2;
    int sec = digit3 * 10 + digit4;
    int ms = digit5 * 10 + digit6;

    if (ms > 60) {
        ms = 0;
        sec++;
    }
    if (sec > 60) {
        sec = 0;
        minute++;
    }
    stoppWatchTime = (minute*10000) + (sec *100) +ms;

}


void overlayText(Vector2 *pos) {
    DrawText(TextFormat("%d/3 Rounds", currentRound), pos->x - 355, pos->y - 320, 40, BLACK);

    int digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0, digit6 = 0;

    digit1 = stoppWatchTime / 100000;
    digit2 = (stoppWatchTime / 10000) % 10;
    digit3 = (stoppWatchTime / 1000) % 10;
    digit4 = (stoppWatchTime / 100) % 10;
    digit5 = (stoppWatchTime / 10) % 10;
    digit6 = stoppWatchTime % 10;

    int minute = digit1 * 10 + digit2;
    int sec = digit3 * 10 + digit4;
    int ms = digit5 * 10 + digit6;

    DrawText(TextFormat("%.2d:%.2d:%.2d", minute, sec, ms), pos->x - 80, pos->y - 300, 60, BLACK);
}
