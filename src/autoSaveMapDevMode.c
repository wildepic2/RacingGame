//
// Created by wildepic on 26/06/2026.
//

#include <stdio.h>

#include "mapManager.h"

//Reads the Map autosave
void readMap() {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("autosave.txt", "r");

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

    // Close the file
    fclose(fptr);
}

void saveMap() {
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("autosave.txt", "w");

    //Parses the matrix to be a long chain of ints
    //Writes the parsed into the autosave.txt
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            int num = mapTextureLocation[i][ii];
            fprintf(fptr, "%d" , num);
        }
    }

    // Close the file
    fclose(fptr);
}
