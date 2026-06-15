//
// Created by wildepic on 15/06/2026.
//

#include "initTextures.h"
#include "state.h"

#include <stddef.h>

Texture2D textures[textureCount];

void initTextures() {
    //Properties for Textures and where are they saved
    const char textureLocation[textureCount][100] = {"assets/bg2.jpg"};
    Vector2 size[textureCount] = { {50, 50}};

    //Inits Textures in the correct Size and if one Texture want load sucessfully the game goes to error srtate
    for (int i = 0; i < textureCount; i++) {
        Image field = LoadImage(textureLocation[i]);

        if (field.data == NULL) {
            TraceLog(LOG_ERROR, "Failed to load image: %s", textureLocation[i]);
            gameState = INIT_ERROR;
            return;
        }

        ImageResize(&field, size[i].x, size[i].y);
        textures[i] = LoadTextureFromImage(field);
        UnloadImage(field);
    }
}