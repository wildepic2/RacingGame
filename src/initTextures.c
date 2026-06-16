//
// Created by wildepic on 15/06/2026.
//

#include "initTextures.h"
#include "state.h"

#include <stddef.h>

Texture2D textures[textureCount];

void initTextures() {
    //Properties for Textures and where are they saved
    const char textureLocation[textureCount][100] = {"assets/car.jpg"};
    Vector2 size[textureCount] = {{50, 50}};

    //Inits Textures in the correct Size and if one Texture want load sucessfully the game goes to error srtate
    for (int i = 0; i < 1; i++) {
        Image field = LoadImage(textureLocation[i]);

        ImageResize(&field, size[i].x, size[i].y);
        textures[i] = LoadTextureFromImage(field);
        UnloadImage(field);
    }
}
