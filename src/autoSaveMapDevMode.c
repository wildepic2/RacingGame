//
// Created by wildepic on 26/06/2026.
//

#include <stdio.h>
#include <stdlib.h>

#include "mapManager.h"
#include "mapString.h"

//if(fptr != NULL) is for not having an error if the file doesnt yet exist
//Reads the Map autosave
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
        char autoSavedOriginStringX[100] = {0};
        char autoSavedOriginStringY[100] = {0};
        fgets(autoSavedOriginStringX, 100, fptr);
        fgets(autoSavedOriginStringY, 100, fptr);
        originX = atoi(autoSavedOriginStringX);
        originY = atoi(autoSavedOriginStringY);
        fclose(fptr);
    }
}

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
}
