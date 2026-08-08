//
// Created by wildepic on 15/06/2026.
//

#include "gameManager.h"

#include <stdio.h>
#include <stdlib.h>

#include "autoSaveMapDevMode.h"
#include "checkpointsManager.h"
#include "countdownGameStart.h"
#include "finishMark.h"
#include "gameOverlayText.h"
#include "highscoreManager.h"
#include "initTextures.h"
#include "mapManager.h"
#include "playerCarManager.h"
#include "state.h"

// Main game loop - executes every frame during active gameplay
// Handles map rendering, player input, checkpoint detection, round management, and finish line crossing
void whilePlaying(Vector2 *playerPos, Camera2D *camera) {
    loadHighScore();
    countdownFun();
    //Loads autosaved map in dev mode
    if (isDev) {
        readMap();
    }
    //Draws The Map
    drawMap(playerPos);
    playerCar(playerPos, camera);
    if (countdown == 0) {
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
}

// Handles game over state - resets game variables and transitions back to menu
// Clears round count, timer, and repositions player car to start position
void gameOver(Vector2 *playerPos) {
    currentRound = 0;
    lassPassTime = 0;
    resetCountdown();
    resetCar(playerPos);
}

// Initializes the game on startup - loads textures, parses map data, and loads highscore
// Sets up all game resources and state required before gameplay begins
void initGame() {
    //Inits the Game Textures
    initTextures();
    mapStringParser();
    loadHighScore();
    calculateCheckpointsStraight();
}
