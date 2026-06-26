//
// Created by wildepic on 23/06/2026.
//

#ifndef RACINGGAME_MAPMANAGER_H
#define RACINGGAME_MAPMANAGER_H
#include "raylib.h"

//Defines the tiles grid sizr
#define mapWidth  100
#define mapHeight 100

void drawMap(Vector2 *pos);
void mapStringParser();
extern int mapTextureLocation[mapWidth][mapHeight];

#endif //RACINGGAME_MAPMANAGER_H
