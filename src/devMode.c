//
// Created by wildepic on 01/07/2026.
//

#include "devMode.h"
#include <stdio.h>
#include "raylib.h"
#include "initTextures.h"
#include "mapManager.h"
#include "autoSaveMapDevMode.h"
#include "mapString.h"

int currentTexture = 0;

void resetMap() {
    if (IsKeyPressed(KEY_R)) {
        for (int i = 0; i < 100; i++) {
            for (int ii = 0; ii < 100; ii++) {
                mapTextureLocation[i][ii] = 0;
            }
        }
        saveMap();
    }
}

void exportMap() {
    if (IsKeyPressed(KEY_F1)) {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("MAP STRING\n");
        for (int i = 0; i < 100; i++) {
            for (int ii = 0; ii < 100; ii++) {
                int num = mapTextureLocation[i][ii];
                printf("%d", num);
                if (ii == 99 && i == 99) {
                    printf(", %d, %d" , originX, originY);
                    printf("\n");
                }
                else {
                    printf(", ");
                }
            }
        }
    }
}

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

void drawDevModeText(Vector2 *pos) {
    DrawText("DEV MODUS", pos->x - 200, pos->y + 290, 80, BLACK);
    DrawText(TextFormat("Current Texture ID: %d", currentTexture), pos->x - 355, pos->y - 300, 40, BLACK);
    DrawText(textureLocation[currentTexture], pos->x - 355, pos->y - 250, 40 ,BLACK);
}

void drawTexture(Vector2 *pos) {
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            if (pos->x < (i * 384) + originX && pos->y < (ii * 384) + originY && pos->x > ((i * 384) - 384) + originX && pos->y > ((ii * 384) - 384) + originY) {
                if (IsKeyDown(KEY_P)) {
                    mapTextureLocation[i][ii] = currentTexture;
                    saveMap();
                }
            }
        }
    }
}

//It allows the car in dev modus to draw the map and export it
void drawMapAsCar(Vector2 *pos) {
    //Resets full dev Map back to grass
    //And autosaves the just grass to the auto dev save
    resetMap();
    //Exports the map string into the cli
    exportMap();
    //select texture arrow keys
    selectTexture();
    //If key O is down you can set in console the origin coords
    enterOrigin();
    //Draw selected texture and shows you are in dev modus
    drawDevModeText(pos);
    //Calculates on which grid square you are and if you press P you draw the selected texture there
    drawTexture(pos);

}