//
// Created by wildepic on 01/07/2026.
//

#include "devMode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "initTextures.h"
#include "mapManager.h"
#include "autoSaveMapDevMode.h"
#include "mapString.h"

int currentTexture = 0;
int currentMode = 0;
int currentMark = 0;

// Resets the entire map to blank grass tiles when 'R' is pressed
// Clears all track tiles, marks, and origin coordinates
void resetMap() {
    if (IsKeyPressed(KEY_R)) {
        for (int i = 0; i < 100; i++) {
            for (int ii = 0; ii < 100; ii++) {
                mapTextureLocation[i][ii] = 0;
            }
        }
        originX = 0;
        originY = 0;
        Vector3 Mark = {0 , 0 , -1};
        startMark = Mark;
        finishMark = Mark;
        saveMap();
    }
}

// Exports the current map configuration as a string to console output (F1 key)
// Outputs map tile data, origin coordinates, and mark positions for map persistence
void exportMap() {
    if (IsKeyPressed(KEY_F1)) {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("MAP STRING\n");
        for (int i = 0; i < 100; i++) {
            for (int ii = 0; ii < 100; ii++) {
                int num = mapTextureLocation[i][ii];
                printf("%d", num);
                if (ii == 99 && i == 99) {
                    printf(", %d, %d, %f, %f, %f, %f, %f, %f", originX, originY, startMark.x , startMark.y , startMark.z , finishMark.x , finishMark.y , finishMark.z);
                    printf("\n");
                } else {
                    printf(", ");
                }
            }
        }
    }
}

// Cycles through available tile textures with UP/DOWN arrow keys in dev mode
void selectTexture() {
    if (IsKeyPressed(KEY_UP)) {
        if (currentTexture < 6) {
            currentTexture++;
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        if (currentTexture > 0) {
            currentTexture--;
        }
    }
}

// Allows entering new map origin coordinates via keyboard input (O key)
void enterOrigin() {
    if (IsKeyDown(KEY_O)) {
        printf("Enter new Origin X: ");
        scanf("%d", &originX);
        printf("Enter new Origin Y: ");
        scanf("%d", &originY);
        printf("New Origin X: %d\nNew Origin Y: %d\n", originX, originY);
        saveMap();
    }
}

// Renders dev mode UI text showing current mode and selected texture information
void drawDevModeText(Vector2 *pos) {
    DrawText("DEV MODUS", pos->x - 200, pos->y + 290, 80, BLACK);
    DrawText(TextFormat("Current MODE: "), pos->x - 355, pos->y - 300, 40, BLACK);
    switch (currentMode) {
        case 0:
            DrawText(TextFormat("Placing Tiles Layer 1"), pos->x - 20, pos->y - 300, 40, BLACK);
            break;

        case 1:
            DrawText(TextFormat("Mark Lines"), pos->x - 20, pos->y - 300, 40, BLACK);
            break;
    }
}

// Places the selected tile texture on the grid tile where the car is located (P key to place)
void drawTexture(Vector2 *pos) {
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if (pos->x < (i * 384) + originX && pos->y < (ii * 384) + originY && pos->x > ((i * 384) - 384) + originX &&
                pos->y > ((ii * 384) - 384) + originY) {
                if (IsKeyDown(KEY_P)) {
                    mapTextureLocation[i][ii] = currentTexture;
                    saveMap();
                }
            }
        }
    }
}

// Dev mode layer 1 - allows placing and selecting road/terrain tiles using arrow keys and P key
void layer1DevMode(Vector2 *pos) {
    //select texture arrow keys
    selectTexture();
    DrawText(TextFormat("Current Texture ID: %d", currentTexture), pos->x - 355, pos->y - 250, 40, BLACK);
    DrawText(textureLocation[currentTexture], pos->x - 355, pos->y - 200, 40,BLACK);
    //Calculates on which grid square you are and if you press P you draw the selected texture there
    drawTexture(pos);
}

// Places a start or finish mark on the road at the car's current position
// Automatically detects road orientation (horizontal/vertical) and sets appropriate direction
void putMark(int i, int ii, char directionText[5]) {
    Vector3 Mark = {};
    //Checks if the road where the mark will be put if its Horizontal or Vertical
    //This will be Put in the Z coord (Texture) of Mark
    if (mapTextureLocation[i][ii] == 1) {
        Mark = (Vector3){i, ii, 0};
        //Because Normally The Up Version is displayed but when the car is pointed down it adds
        //one to the Z what displays the Down Version or better said it inverts it
        if (strcmp(directionText, "down") == 0) {
            Mark.z++;
        }
    }
    if (mapTextureLocation[i][ii] == 2) {
        Mark = (Vector3){i, ii, 2};
        //Because Normally The Left Version is displayed but when the car is pointed Right it adds
        //one to the Z what displays the Right Version or better said it inverts it
        if (strcmp(directionText, "right") == 0) {
            Mark.z++;
        }
    }

    //Checks again if we are on a road because Mark could else draw the marks where there are no roads
    //Because the funtion is called on every grid square and Vector 3 Mark is 0 default whats good enough to draw it
    if ((mapTextureLocation[i][ii] == 1 || mapTextureLocation[i][ii] == 2)) {
        //Chooses If it draws Finish or Start Mark
        //Also Checks if the Mark isnt the Position of the Old Mark and also the other mark
        //If all correct it updates the pos and direction of the mark
        if (currentMark == 0 && (Mark.x != startMark.x || Mark.y != startMark.y || Mark.z != startMark.z) && (
                Mark.x != finishMark.x || Mark.y != finishMark.y)) {
            startMark = Mark;
        }
        if (currentMark == 1 && (Mark.x != finishMark.x || Mark.y != finishMark.y || Mark.z != finishMark.z) && (
                Mark.x != startMark.x || Mark.y != startMark.y)) {
            finishMark = Mark;
        }
    }
}

// Detects the car's current grid position and places a mark there when P is pressed
void drawMark(Vector2 *pos, char directionText[5]) {
    //Calculates the grid square of the car
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if (pos->x < (i * 384) + originX && pos->y < (ii * 384) + originY && pos->x > ((i * 384) - 384) + originX &&
                pos->y > ((ii * 384) - 384) + originY) {
                //If you press P it calls putMark
                if (IsKeyDown(KEY_P)) {
                    putMark(i, ii, directionText);
                    saveMap();
                }
            }
        }
    }
}

// Cycles between start mark and finish mark selection using UP/DOWN arrow keys
void chooseMark() {
    if (IsKeyPressed(KEY_UP)) {
        if (currentMark < 1) {
            currentMark++;
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        if (currentMark > 0) {
            currentMark--;
        }
    }
}

// Displays which mark type (start or finish) is currently selected for placement
void displaySelectedMarkText(Vector2 *pos) {
    DrawText(TextFormat("Current Mark: "), pos->x - 355, pos->y - 250, 40, BLACK);
    if (currentMark == 0) {
        DrawText(TextFormat("Start Mark"), pos->x - 50, pos->y - 250, 40,BLACK);
    }
    if (currentMark == 1) {
        DrawText(TextFormat("Finish Mark"), pos->x - 50, pos->y - 250, 40,BLACK);
    }
}

// Dev mode layer 2 - handles placing start and finish marks on the race track
void startStopMarkAddMode(Vector2 *pos, char directionText[5]) {
    chooseMark();
    displaySelectedMarkText(pos);
    drawMark(pos, directionText);
}

// Routes dev mode functionality to appropriate handler based on current mode
void modeSwitch(Vector2 *pos, char directionText[5]) {
    if (currentMode == 0) {
        layer1DevMode(pos);
    } else if (currentMode == 1) {
        startStopMarkAddMode(pos, directionText);
    }
}

// Toggles between dev mode layers using LEFT/RIGHT arrow keys
void selectMode() {
    if (IsKeyPressed(KEY_LEFT)) {
        if (currentMode < 1) {
            currentMode++;
        }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (currentMode > 0) {
            currentMode--;
        }
    }
}

// Main dev mode function - enables map editing with tile placement, mark placement, and map export
// Provides UI for selecting textures, placing marks, and saving map changes
void drawMapAsCar(Vector2 *pos, char directionText[5]) {
    //Resets full dev Map back to grass
    //And autosaves the just grass to the auto dev save
    resetMap();
    //Exports the map string into the cli
    exportMap();
    //If key O is down you can set in console the origin coords
    enterOrigin();
    //Draw selected texture and shows you are in dev modus
    drawDevModeText(pos);

    selectMode();
    modeSwitch(pos, directionText);
}
