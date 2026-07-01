//
// Created by wildepic on 01/07/2026.
//

#include "errorManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

ErrorType errorType = UNDEFINED;
char errorMessage[94];


//Makes the error type of enum to char
void errorTypeToString(char errorTypeText[]) {
    switch (errorType) {
        case UNDEFINED:
            strcpy(errorTypeText, "Undefined Error");
            break;
        case INIT_ERROR:
            strcpy(errorTypeText, "Init Error");
            break;
    }
}

void errorTextParser(char errorMessageHalf1[], char errorMessageHalf2[]) {
    int i =0;
    //Copies 1 half
    for (int ii = 0; ii < 47; ii++) {
        errorMessageHalf1[ii] = errorMessage[i];
        i++;
    }
    //Copies 2 Half
    for (int ii = 0; ii < 47; ii++) {
        errorMessageHalf2[ii] = errorMessage[i];
        i++;
    }
}

//Calculates how many pixels one string needs
void calculatePixelLength(char errorMessageHalf1[], char errorMessageHalf2[], int *pixelLength1, int *pixelLength2) {
    *pixelLength1 = strlen(errorMessageHalf1) * 17;
    *pixelLength2 = strlen(errorMessageHalf2) * 17;
}

//Calculates which x coord should the char start for it to be center
int calculateXCoordtoDraw(int pixelLength) {
    int xCoord = (GetScreenWidth()- pixelLength) / 2;
    return xCoord;
}

void errorMenu() {
    char errorMessageHalf1[51] = {0};
    char errorMessageHalf2[51] = {0};
    char errorTypeText[100] = {0};
    int pixelLength1 = 0;
    int pixelLength2 = 0;

    errorTypeToString(errorTypeText);
    errorTextParser(errorMessageHalf1 , errorMessageHalf2);
    calculatePixelLength(errorMessageHalf1, errorMessageHalf2, &pixelLength1, &pixelLength2);

    //Draws error type and error message
    DrawText(errorTypeText, 270, 150, 50, RED);
    DrawText(errorMessageHalf1, calculateXCoordtoDraw(pixelLength1), 230, 31, BLACK);
    DrawText(errorMessageHalf2, calculateXCoordtoDraw(pixelLength2), 270, 31, BLACK);

    //Key Press SPACE to Exit
    DrawText("Press SPACE to Quit", 190, 450, 40, BLACK);
    if (IsKeyDown(KEY_SPACE)) {
        exit(0);
    }
}
