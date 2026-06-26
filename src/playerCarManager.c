//
// Created by wildepic on 15/06/2026.
//

#include <stdio.h>

#include "raylib.h"
#include "playerCarManager.h"

#include <stdlib.h>
#include <string.h>

#include "initTextures.h"
#include "mapManager.h"
#include "state.h"

float speed = 0.00f;
//Top speed 300 kmh
//Acceleration 3 second 0 to 100 kmh
const float accelerationSpeedFrame = 0.0959f;
const float deaccelerationSpeedFrame = 0.00508f;
const float brakeSpeedFrame = 0.1059f;
const float maxSpeed = 51.81f;

int currentTexture = 0;
//Saves which button of WASD where saved
bool direction[4] = {false, false, false, false};
//Saved the direction the car os showing
char directionText[5];
int rotation = 0;
//Draws the player Car
void drawPlayerCar(Vector2 pos, char text[]) {
    if (strcmp(text, "up") == 0) {
        DrawTextureEx(textures[0], pos, rotation, 1.0f, WHITE);
    } else if (strcmp(text, "down") == 0) {
        DrawTextureEx(textures[1], pos, rotation, 1.0f, WHITE);
    } else if (strcmp(text, "right") == 0) {
        DrawTextureEx(textures[3], pos, rotation, 1.0f,WHITE);
    } else if (strcmp(text, "left") == 0) {
        DrawTextureEx(textures[2], pos, rotation, 1.0f,WHITE);
    }
}

//Makes the car speed be bigger with acceleration until it reaches max speed
//Acceleration will only then get bigger if you press one button move keys
void carAcceleration(float *speed) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
        if (*speed < maxSpeed) {
            *speed += accelerationSpeedFrame;
        }
    }
}

//Makes the car brake with brake speed until car has no speed
//Because it often goes into minus whats an problem when its minus it auto sets the speed 0
void carBrake(float *speed) {
    if (*speed <= 0) {
        speed = 0;
    } else {
        *speed -= brakeSpeedFrame;
    }
}

void playerInput(bool direction[4]) {
    //If you pressed one key it resets it which direction did the car move
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
        direction[0] = false;
        direction[1] = false;
        direction[2] = false;
        direction[3] = false;
    }

    //Sets in which direction the car moves
    if (IsKeyDown(KEY_W)) {
        direction[3] = false;
        direction[2] = true;
    } else if (IsKeyDown(KEY_S)) {
        direction[2] = false;
        direction[3] = true;
    }
    if (IsKeyDown(KEY_A)) {
        direction[1] = false;
        direction[0] = true;
    } else if (IsKeyDown(KEY_D)) {
        direction[0] = false;
        direction[1] = true;
    }
    //Space brake
    if (IsKeyDown(KEY_SPACE)) {
        carBrake(&speed);
    }
}

void carMovement(Vector2 *pos, bool direction[4]) {
    //Make the car with the speed move into the direction
    //Left
    if (direction[0]) {
        pos->x -= speed;
    }
    //Right
    if (direction[1]) {
        pos->x += speed;
    }
    //Up
    if (direction[2]) {
        pos->y -= speed;
    }
    //Down
    if (direction[3]) {
        pos->y += speed;
    }
}

//Coasting with an bit of disacceleration
void carDisacceleration(float *speed) {
    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
        if (*speed > 0) {
            *speed -= deaccelerationSpeedFrame;
        } else {
            *speed = 0;
        }
    }
}

//sets the direction of the car where to move
void carDirection(char directionText[], bool direction[4]) {
    rotation = 0;
    strcpy(directionText, "up");
    //Left Up diagonal
    if (direction[0] && direction[2]) {
        strcpy(directionText, "left");
        rotation = 45;
    }
    //Right Up diagonal
    else if (direction[1] && direction[2]) {
        strcpy(directionText, "up");
        rotation = 45;
    }
    //Left Down diagonal
    else if (direction[0] && direction[3]) {
        strcpy(directionText, "down");
        rotation = 45;
    }
    //Right Down diagonal
    else if (direction[1] && direction[3]) {
        strcpy(directionText, "right");
        rotation = 45;
    }
    //Left
    else if (direction[0]) {
        strcpy(directionText, "left");
    }
    //Right
    else if (direction[1]) {
        strcpy(directionText, "right");
    }
    //Up
    else if (direction[2]) {
        strcpy(directionText, "up");
    }
    //Down
    else if (direction[3]) {
        strcpy(directionText, "down");
    }
}

void updateCamera(Camera2D *camera, Vector2 *pos) {
    camera->target = (Vector2){pos->x, pos->y};
    camera->offset = (Vector2){375, 375};
}
//It allows the car in dev modus to draw the map and export it
void drawMapAsCar(Vector2 *pos) {
    //Exports the map string into the cli
    if (IsKeyPressed(KEY_F1)) {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("MAP STRING\n");
        for (int i = 0; i < 100; i++) {
            for (int ii = 0; ii < 100; ii++) {
                int num = mapTextureLocation[i][ii];
                printf("%d", num);
                if (ii == 99 && i == 99) {
                    //exit(0);
                    printf("\n");
                }
                else {
                    printf(", ");
                }
            }
        }
    }
    //select texture arrow keys
    if (IsKeyPressed(KEY_UP)) {
        if (currentTexture < textureCount - 1) {
            currentTexture++;
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        if (currentTexture > 0) {
            currentTexture--;
        }
    }
    //Draw selected texture and shows you are in dev modusw
    DrawText("DEV MODUS", pos->x - 200, pos->y + 290, 80, BLACK);
    DrawText(TextFormat("Current Texture ID: %d", currentTexture), pos->x - 355, pos->y - 300, 40, BLACK);
    DrawText(textureLocation[currentTexture], pos->x - 355, pos->y - 250, 40 ,BLACK);
    //Calculates on which grid square you are and if you press P you draw the selected texture there
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if (pos->x < i * 384 && pos->y < ii * 384 && pos->x > (i * 384) - 384 && pos->y > (ii * 384) - 384) {
                if (IsKeyDown(KEY_P)) {
                    mapTextureLocation[i][ii] = currentTexture;
                }
            }
        }
    }
}

//All functions for Player Car
void playerCar(Vector2 *pos, Camera2D *camera) {
    updateCamera(camera, pos);
    //Starts the camera mode
    BeginMode2D(*camera);
    //Draws the car
    drawPlayerCar(*pos, directionText);
    //Calculates the kmh
    float kmhCalculated = speed * 5.79f;
    //IF dev modus it allows to draw the map and export it as map string
    if (isDev) {
        drawMapAsCar(pos);
    }
    //Draws The KMH
    DrawText(TextFormat("%0.2f km/h", kmhCalculated), pos->x - 355, pos->y - 355, 40, BLACK);
    //Stop the camera mode
    EndMode2D();

    playerInput(direction);
    carAcceleration(&speed);
    carDisacceleration(&speed);
    carMovement(pos, direction);
    carDirection(directionText, direction);
}
