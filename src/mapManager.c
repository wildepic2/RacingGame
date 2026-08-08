//
// Created by wildepic on 23/06/2026.
//

#include "mapManager.h"

#include <stdlib.h>

#include "initTextures.h"
#include "mapString.h"
#include "raylib.h"
#include "state.h"

// Defines for every tile on the grid the size
#define gridWidth 384
#define gridHeight 384
// Stores which tile ID to use for which tile
int mapTextureLocation[100][100] = {0};

int originX = 0;
int originY = 0;

Vector3 startMark;
Vector3 finishMark;

// Parses the hardcoded map string into a 2D tile array and extracts map metadata
// Extracts map origin, start mark position/direction, and finish mark position/direction
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
    startMark = (Vector3) {mapString[j + 2], mapString[j + 3], mapString[j + 4]};
    finishMark = (Vector3) {mapString[j + 5], mapString[j + 6], mapString[j + 7]};
}

// Renders the start and finish line marks on the map at their defined positions
// Only draws marks if they are defined (not -1 in z-coordinate)
void drawMarks(Vector2 *pos) {
    int texture = startMark.z + 7;
    if (startMark.z != -1) {
        DrawTexture(textures[texture], ((startMark.x * gridWidth) - pos->x) + 20 + originX,
                    ((startMark.y * gridHeight) - pos->y) + 20 + originY, WHITE);
    }
    if (finishMark.z != -1) {
        texture = finishMark.z + 15;
        DrawTexture(textures[texture], ((finishMark.x * gridWidth) - pos->x) + 20 + originX,
                    ((finishMark.y * gridHeight) - pos->y) + 20 + originY, WHITE);
    }
}

// Renders the entire game map including grass background and road tiles
// Applies camera offset so the map moves relative to the player's position
void drawMap(Vector2 *pos) {
    for (int i = -2; i < mapWidth + 2; i++) {
        for (int ii = -2; ii < mapHeight + 2; ii++) {
            if (isDev == false) {
                DrawTexture(textures[0], ((i * gridWidth) - pos->x) + originX, ((ii * gridHeight) - pos->y) + originY,
                            WHITE);
            }
        }
    }
    // Draws the Tiles on Right place
    // The tiles X Y starts from the Origin Declared above
    // Calculates Them where they should be that they move and look like the car moves but they move
    for (int i = 0; i < mapWidth; i++) {
        for (int ii = 0; ii < mapHeight; ii++) {
            DrawTexture(textures[mapTextureLocation[i][ii]], ((i * gridWidth) - pos->x) + originX,
                        ((ii * gridHeight) - pos->y) + originY, WHITE);
        }
    }
    drawMarks(pos);
}
