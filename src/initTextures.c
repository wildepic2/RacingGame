//
// Created by wildepic on 15/06/2026.
//

#include "initTextures.h"
#include "state.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errorManager.h"

Texture2D textures[textureCount];

//Properties for Textures and where are they saved
const char textureLocation[textureCount][100] = {
    {"assets/green_ground.png"}, //0
    {"assets/straight_road_up_down.png"}, //1
    {"assets/straight_road_left_right.png"}, //2
    {"assets/corner_left.png"}, //3
    {"assets/corner_right.png"}, //4
    {"assets/corner_left_down.png"}, //5
    {"assets/corner_right_down.png"}, //6
    {"assets/start_line_mark.png"}, //7
    {"assets/start_line_mark_down.png"}, //8
    {"assets/start_line_mark_left.png"}, //9
    {"assets/start_line_mark_right.png"}, //10
    {"assets/car_up.png"}, //11
    {"assets/car_down.png"}, //12
    {"assets/car_left.png"}, //13
    {"assets/car_right.png"}, //14
    {"assets/finish_line_mark.png"}, //15
    {"assets/finish_line_mark_down.png"}, //16
    {"assets/finish_line_mark_left.png"}, //17
    {"assets/finish_line_mark_right.png"}, //18
};

// Initializes all game textures by loading them from asset files and resizing to appropriate dimensions
// If any texture fails to load, triggers an error state with details of which texture is missing
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
            strcpy(errorMessage, TextFormat("Texture Missing: %s", textureLocation[i]));
            break;
        }

        UnloadImage(field);
    }
}
