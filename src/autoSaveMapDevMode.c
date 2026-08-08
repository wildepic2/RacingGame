//
// Created by wildepic on 26/06/2026.
//

#include <stdio.h>
#include <stdlib.h>

#include "mapManager.h"
#include "mapString.h"

// Loads the dev mode map autosave from file storage into the game
// Restores map tiles, origin coordinates, and start/finish mark positions
void readMap() {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("autosave_level_1.txt", "r");
    if (fptr != NULL) {
        // Store the content of the file
        char autoSavedMapString[10001];

        // Read the content and store it inside myString
        fgets(autoSavedMapString, 10001, fptr);

        int j = 0;
        //Parses the content of autosave
        for (int i = 0; i < 100; i++) {
            for (int ii = 0; ii < 100; ii++) {
                int num = autoSavedMapString[j] - '0';
                mapTextureLocation[i][ii] = num;
                j++;
            }
        }
        fclose(fptr);
    }
    //Loads the origin from the save
    fptr = fopen("autosave_origin.txt", "r");
    if (fptr != NULL) {
        char buffer[100] = {0};
        fgets(buffer, 100, fptr);
        originX = atoi(buffer);
        fgets(buffer, 100, fptr);
        originY = atoi(buffer);
        fclose(fptr);
    }

    fptr = fopen("autosave_marks.txt", "r");
    if (fptr != NULL) {
        char buffer[100] = {0};
        fgets(buffer, 100, fptr);
        startMark.x = atof(buffer);
        fgets(buffer, 100, fptr);
        startMark.y = atof(buffer);
        fgets(buffer, 100, fptr);
        startMark.z = atof(buffer);
        fgets(buffer, 100, fptr);
        finishMark.x = atof(buffer);
        fgets(buffer, 100, fptr);
        finishMark.y = atof(buffer);
        fgets(buffer, 100, fptr);
        finishMark.z = atof(buffer);
        fclose(fptr);
    }
}

// Saves the current map configuration to file storage for dev mode persistence
// Writes map tiles, origin coordinates, and start/finish mark positions to separate files
void saveMap() {
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("autosave_level_1.txt", "w");

    //Parses the matrix to be a long chain of ints
    //Writes the parsed into the autosave.txt
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            int num = mapTextureLocation[i][ii];
            fprintf(fptr, "%d", num);
        }
    }

    // Close the file
    fclose(fptr);
    //Save the origin to the origin auto save file
    fptr = fopen("autosave_origin.txt", "w");
    fprintf(fptr, "%d\n", originX);
    fprintf(fptr, "%d\n", originY);
    fclose(fptr);

    //Autosaves the start and finish marks
    fptr = fopen("autosave_marks.txt", "w");
    fprintf(fptr, "%f\n", startMark.x);
    fprintf(fptr, "%f\n", startMark.y);
    fprintf(fptr, "%f\n", startMark.z);
    fprintf(fptr, "%f\n", finishMark.x);
    fprintf(fptr, "%f\n", finishMark.y);
    fprintf(fptr, "%f\n", finishMark.z);
    fclose(fptr);
}
