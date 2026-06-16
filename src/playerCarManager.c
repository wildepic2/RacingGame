//
// Created by wildepic on 15/06/2026.
//

#include <stdio.h>

#include "raylib.h"
#include "playerCarManager.h"

#include "initTextures.h"

float speed =0.00f;
//Top speed 300 kmh
//Acceleration 3 second 0 to 100 kmh
//10 Pixel equals 1 meter
const float accelerationSpeedFrame = 0.0257f;
const float deaccelerationSpeedFrame = 0.00136f;
const float brakeSpeedFrame = 0.0109f;
const float maxSpeed = 13.89f;

bool direction[4] = {false, false, false, false};

//Draws the player Car
void drawPlayerCar(Vector2 pos , float rotation) {
    DrawTextureEx(textures[0], pos, rotation, 1,WHITE);
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
    }
    else {
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
    }
    else if (IsKeyDown(KEY_S)) {
        direction[2] = false;
        direction[3] = true;
    }
    if (IsKeyDown(KEY_A)) {
        direction[1] = false;
        direction[0] = true;
    }
    else if (IsKeyDown(KEY_D)) {
        direction[0] = false;
        direction[1] = true;
    }
    //Space brake
    if (IsKeyDown(KEY_SPACE)) {
        carBrake(&speed);
    }
}

void carMovement(Vector2 *pos , bool direction[4]) {
    //Make the car with the speed move into the direction
    if (direction[0]) {
        pos->x -= speed;
    }
    if (direction[1]) {
        pos->x += speed;
    }
    if (direction[2]) {
        pos->y -= speed;
    }
    if (direction[3]) {
        pos->y += speed;
    }
}

//Coasting with an bit of disacceleration
void carDisacceleration(float *speed) {
    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
        if (*speed > 0) {
            *speed -= deaccelerationSpeedFrame;
        }
        else {
            *speed = 0;
        }
    }
}


//ALl functions for Player Car
void playerCar(Vector2 *pos , float *rotation) {
    drawPlayerCar(*pos, *rotation);
    playerInput(direction);
    carAcceleration(&speed);
    carDisacceleration(&speed);
    carMovement(pos, direction);
    float kmhCalculated = speed * 21.6f;
    DrawText(TextFormat("%0.2f km/h", kmhCalculated), pos->x - 355, pos->y - 355, 40, BLACK);
}
