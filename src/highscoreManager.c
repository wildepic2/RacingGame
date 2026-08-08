//
// Created by wildepic on 8/1/26.
//

#include "highscoreManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "state.h"

// Loads the highscore from file storage into the highscore global variable
// If the file doesn't exist, the default highscore remains unchanged
void loadHighScore() {
    FILE *fptr;
    fptr = fopen("highscore.txt", "r");
    if (fptr != NULL) {
        char buffer[100] = {0};
        fgets(buffer, 100, fptr);
        highscore = atoi(buffer);
        fclose(fptr);
    }
}

// Saves the current race time to highscore file if it beats the previous best
void autosaveHighscore() {
    if (stoppWatchTime < highscore) {
        FILE *fptr;
        fptr = fopen("highscore.txt", "w");
        fprintf(fptr, "%d", stoppWatchTime);
        fclose(fptr);
    }
}
