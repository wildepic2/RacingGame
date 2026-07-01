//
// Created by wildepic on 23/06/2026.
//

#include "mapManager.h"

#include <stdlib.h>

#include "initTextures.h"
#include "raylib.h"
#include "mapString.h"

//Defines for every tile on the grid the size
#define gridWidth 384
#define gridHeight 384
//Stores which tile ID to use for which tile
int mapTextureLocation[100][100] = {0};

int originX = 0;
int originY = 0;

Vector3 startMark;
Vector3 finishMark;

//Loads the map string into the mapTextureLocation Matrix
void mapStringParser() {
    int j = 0;
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            mapTextureLocation[i][ii] = mapString[j];
            j++;
        }
    }
    originX = mapString[j];
    originY = mapString[j + 1];
    startMark = (Vector3){mapString[j + 2], mapString[j + 3], mapString[j + 4]};
    finishMark = (Vector3){mapString[j + 5], mapString[j + 6], mapString[j + 7]};
}

void drawMap(Vector2 *pos) {
    //Draws the Tiles on Right place
    //The tiles X Y starts from the Origin Declared above
    //Calculates Them where they should be that they move and look like the car moves but they move
    for (int i = 0; i < mapWidth; i++) {
        for (int ii = 0; ii < mapHeight; ii++) {
            DrawTexture(textures[mapTextureLocation[i][ii]], ((i * gridWidth) - pos->x) + originX,
                        ((ii * gridHeight) - pos->y) + originY,WHITE);
        }
    }
    int texture = startMark.z + 7;
    DrawTexture(textures[texture], (startMark.x * gridWidth) - pos->x, (startMark.y * gridHeight) - pos->y, WHITE);
    texture = finishMark.z + 15;
    DrawTexture(textures[texture], (finishMark.x * gridWidth) - pos->x, (finishMark.y * gridHeight) - pos->y, WHITE);
}
