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


void resetCounter() {
    counter = counted;
    for (int i = 0; i <100 ; i++) {
        for (int ii = 0; ii <100 ; ii++) {
            usedCheckpoints[i][ii] = false;
        }
    }
}

void calculateIandIIofPlayer(Vector2 *pos , int *x , int *y) {
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

void checkpointPass(Vector2 *pos) {
    int i , ii;
    calculateIandIIofPlayer(pos , &i , &ii);
    if ((mapTextureLocation[i][ii] == 1 || mapTextureLocation[i][ii] == 2) && usedCheckpoints[i][ii] == false) {
        usedCheckpoints[i][ii] = true;
        counter--;
    }
}

void calculateCheckpointsStraight() {
    for (int i = 0; i <100 ; i++) {
        for (int ii = 0; ii <100 ; ii++) {
            if ((mapTextureLocation[i][ii] == 1 || mapTextureLocation[i][ii] == 2)) {
                counted++;
            }
        }
    }
    counter = counted;
}
