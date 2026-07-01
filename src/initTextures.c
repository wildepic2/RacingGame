//
// Created by wildepic on 15/06/2026.
//

#include "initTextures.h"
#include "state.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errorManager.h"

Texture2D textures[textureCount];

//Properties for Textures and where are they saved
const char textureLocation[textureCount][100] = {
    {"assets/green_ground.png"},
    {"assets/straight_road_up_down.png"},
    {"assets/straight_road_left_right.png"},
    {"assets/corner_left.png"},
    {"assets/corner_right.png"},
    {"assets/corner_left_down.png"},
    {"assets/corner_right_down.png"},
    {"assets/start_line_mark.png"},
    {"assets/start_line_mark_down.png"},
    {"assets/start_line_mark_left.png"},
    {"assets/start_line_mark_right.png"},
    {"assets/car_up.png"},
    {"assets/car_down.png"},
    {"assets/car_left.png"},
    {"assets/car_right.png"},
    {"assets/finish_line_mark.png"},
    {"assets/finish_line_mark_down.png"},
    {"assets/finish_line_mark_left.png"},
    {"assets/finish_line_mark_right.png"},
};

void initTextures() {
    Vector2 size[textureCount] = {
        {384, 384},
        {384, 384},
        {384, 384},
        {384, 384},
        {384, 384},
        {384, 384},
        {384, 384},
        {343, 189},
        {343, 189},
        {189, 343},
        {189, 343},
        {96, 179},
        {96, 179},
        {179, 96},
        {176, 96},
        {343, 189},
        {343, 189},
        {189, 343},
        {189, 343},
    };

    //Inits Textures in the correct Size and if one Texture want load sucessfully the game goes to error srtate
    for (int i = 0; i < textureCount; i++) {
        Image field = LoadImage(textureLocation[i]);
        ImageResize(&field, size[i].x, size[i].y);
        textures[i] = LoadTextureFromImage(field);

        if (textures[i].id == 0) {
            gameState = ERROR_STATE;
            errorType = INIT_ERROR;
            strcpy(errorMessage, TextFormat("Texture Missing: %s" , textureLocation[i]));
            break;
        }

        UnloadImage(field);
    }
}
