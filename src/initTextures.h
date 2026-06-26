//
// Created by wildepic on 15/06/2026.
//
#ifndef RACINGGAME_INITTEXTURES_H
#define RACINGGAME_INITTEXTURES_H
#include "raylib.h"

//Defines how maby textures they are
#define textureCount 11
//Texture2D array where all textures are saved
extern Texture2D textures[textureCount];
extern const char textureLocation[textureCount][100];

void initTextures();

#endif //RACINGGAME_INITTEXTURES_H
