//
// Created by wildepic on 30/07/2026.
//

#include "gameOverlayText.h"

#include "raylib.h"
#include "state.h"

void timer() {
    //Increments Stoppwatch
    stoppWatchTime+=1;

    //get every digit of the variable stopWatchtime
    int digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0, digit6 = 0;
    digit1 = stoppWatchTime / 100000;
    digit2 = (stoppWatchTime / 10000) % 10;
    digit3 = (stoppWatchTime / 1000) % 10;
    digit4 = (stoppWatchTime / 100) % 10;
    digit5 = (stoppWatchTime / 10) % 10;
    digit6 = stoppWatchTime % 10;

    //Reconstructs the digits into minute second and milli second
    int minute = digit1 * 10 + digit2;
    int sec = digit3 * 10 + digit4;
    int ms = digit5 * 10 + digit6;

    //If ms is over 60 it sets it to 0 and increment sec
    if (ms > 60) {
        ms = 0;
        sec++;
    }
    //If sec is over 60 it sets it to 0 and increment minute
    if (sec > 60) {
        sec = 0;
        minute++;
    }
    //Reconstructs the stoppwatchtime from minute second and millisecond
    stoppWatchTime = (minute*10000) + (sec *100) +ms;

}

//Shows Round and timer
void overlayText(Vector2 *pos) {
    DrawText(TextFormat("%d/3 Rounds", currentRound), pos->x - 355, pos->y - 320, 40, BLACK);

    //Get every digit from stoppwatch timer variable
    int digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0, digit6 = 0;

    digit1 = stoppWatchTime / 100000;
    digit2 = (stoppWatchTime / 10000) % 10;
    digit3 = (stoppWatchTime / 1000) % 10;
    digit4 = (stoppWatchTime / 100) % 10;
    digit5 = (stoppWatchTime / 10) % 10;
    digit6 = stoppWatchTime % 10;
    //Reconstructs the digits to minute second and milli second
    int minute = digit1 * 10 + digit2;
    int sec = digit3 * 10 + digit4;
    int ms = digit5 * 10 + digit6;

    //Shows Timer
    DrawText(TextFormat("%.2d:%.2d:%.2d", minute, sec, ms), pos->x - 80, pos->y - 300, 60, BLACK);
    DrawText(TextFormat("Best: %.2d:%.2d:%.2d", 0, 0, 0), pos->x - 10, pos->y - 360, 60, RED);
}
