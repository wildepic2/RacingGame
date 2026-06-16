//
// Created by wildepic on 15/06/2026.
//

#include "initTextures.h"
#include "state.h"

#include <stddef.h>

Texture2D textures[textureCount];

void initTextures() {
    //Properties for Textures and where are they saved
    const char textureLocation[textureCount][100] = {
        {"assets/car_up.png"} ,
        {"assets/car_down.png"},
        {"assets/car_left.png"},
        {"assets/car_right.png"}

    } ;
    Vector2 size[textureCount] = {
        {96, 179},
        {96, 179},
        {179, 96},
        {176, 96},
    };

    //Inits Textures in the correct Size and if one Texture want load sucessfully the game goes to error srtate
    for (int i = 0; i < textureCount; i++) {
        Image field = LoadImage(textureLocation[i]);

        ImageResize(&field, size[i].x, size[i].y);
        textures[i] = LoadTextureFromImage(field);
        UnloadImage(field);
    }
}
