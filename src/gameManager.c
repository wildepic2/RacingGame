//
// Created by wildepic on 15/06/2026.
//

#include "gameManager.h"

#include <stdio.h>
#include <stdlib.h>

#include "autoSaveMapDevMode.h"
#include "checkpointsManager.h"
#include "finishMark.h"
#include "gameOverlayText.h"
#include "highscoreManager.h"
#include "initTextures.h"
#include "mapManager.h"
#include "playerCarManager.h"
#include "state.h"

//Runs on every frame
void whilePlaying(Vector2 *playerPos, Camera2D *camera) {
    loadHighScore();
    //Loads autosaved map in dev mode
    if (isDev) {
        readMap();
    }
    //Draws The Map
    drawMap(playerPos);
    playerCar(playerPos, camera);
    timer();
    checkpointPass(playerPos);

    if (finishMarkPass(playerPos) && isDev == false) {
        if (currentRound < 3 && counter == 0) {
            currentRound++;
            resetCounter();
        }
        else if (counter == 0) {
            autosaveHighscore();
            loadHighScore();
            resetCounter();
            gameState = GAME_OVER;
        }
    }
}

//Runs every frame when the gameState is Gameover
void gameOver() {
    currentRound = 0;
    lassPassTime = 0;
}

//Runs on init game
void initGame() {
    //Inits the Game Textures
    initTextures();
    mapStringParser();
    loadHighScore();
    calculateCheckpointsStraight();
}
