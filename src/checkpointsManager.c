//
// Created by wildepic on 8/2/26.
//

#include "checkpointsManager.h"

#include <stdio.h>

#include "mapManager.h"
#include "mapString.h"
int counted = 0;
int counter = 0;
bool usedCheckpoints[100][100] = {false};


// Resets the checkpoint counter and marks all checkpoints as unused for the current lap/round
void resetCounter() {
    counter = counted;
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            usedCheckpoints[i][ii] = false;
        }
    }
}

// Determines which grid tile the player's car is currently positioned on
// Calculates x and y tile indices based on car position and tile size (384x384)
void calculateIandIIofPlayer(Vector2 *pos, int *x, int *y) {
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if (pos->x < (i * 384) + originX && pos->y < (ii * 384) + originY && pos->x > ((i * 384) - 384) + originX &&
                pos->y > ((ii * 384) - 384) + originY) {
                *x = i;
                *y = ii;
                return;
            }
        }
    }
}

// Detects when the player's car passes a checkpoint tile
// Decrements checkpoint counter when a new checkpoint (road type 1 or 2) is reached
void checkpointPass(Vector2 *pos) {
    int i, ii;
    calculateIandIIofPlayer(pos, &i, &ii);
    if ((mapTextureLocation[i][ii] == 1 || mapTextureLocation[i][ii] == 2) && usedCheckpoints[i][ii] == false) {
        usedCheckpoints[i][ii] = true;
        counter--;
    }
}

// Counts all checkpoint tiles on the map and initializes the checkpoint counter
// This function is called during game initialization to set up the checkpoint system
void calculateCheckpointsStraight() {
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if ((mapTextureLocation[i][ii] == 1 || mapTextureLocation[i][ii] == 2)) {
                counted++;
            }
        }
    }
    counter = counted;
}
