//
// Created by wildepic on 8/1/26.
//

#include "finishMark.h"

#include <stdio.h>
#include <string.h>

#include "mapManager.h"
#include "mapString.h"
#include "raylib.h"
#include "state.h"

int lassPassTime = 0;
int directionCar = 0;

void getCarDirection(char directionTextGot[5]) {
    if (strcmp(directionTextGot, "up") == 0) {
        directionCar = 0;
    }
    else if (strcmp(directionTextGot, "down") == 0) {
        directionCar = 1;
    }
    else if (strcmp(directionTextGot, "left") == 0) {
        directionCar = 2;
    }
    else if (strcmp(directionTextGot, "right") == 0) {
        directionCar = 3;
    }
}

bool finishMarkPass(Vector2 *pos) {
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if (pos->x < (i * 384) + originX && pos->y < (ii * 384) + originY && pos->x > ((i * 384) - 384) + originX &&
                pos->y > ((ii * 384) - 384) + originY) {
                if (finishMark.x == i && finishMark.y == ii && lassPassTime + 100 < stoppWatchTime && finishMark.z == directionCar) {
                    lassPassTime = stoppWatchTime;
                    return true;
                }
            }
        }
    }
    return false;
}
