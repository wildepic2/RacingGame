//
// Created by wildepic on 8/2/26.
//

#ifndef RACINGGAME_CHECKPOINTSMANAGER_H
#define RACINGGAME_CHECKPOINTSMANAGER_H
#include "raylib.h"

void calculateCheckpointsStraight();
void checkpointPass(Vector2 *pos);
void resetCounter();
extern int counter;

#endif // RACINGGAME_CHECKPOINTSMANAGER_H
