//
// Created by wildepic on 8/1/26.
//

#include "highscoreManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "state.h"

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

void autosaveHighscore() {
    if (stoppWatchTime < highscore) {
        FILE *fptr;
        fptr = fopen("highscore.txt", "w");
        fprintf(fptr, "%d", stoppWatchTime);
        fclose(fptr);
    }
}
