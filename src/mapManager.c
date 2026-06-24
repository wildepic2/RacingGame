//
// Created by wildepic on 23/06/2026.
//

#include "mapManager.h"

#include <stdlib.h>

#include "initTextures.h"
#include "raylib.h"

//Defines for every tile on the grid the size
#define gridWidth 384
#define gridHeight 384
//Origin for Tile Drawing
const int originX = 0;
const int originY = 0;
//Stores which tile ID to use for which tile
int mapTextureLocation[100][100] = {0};

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
}
