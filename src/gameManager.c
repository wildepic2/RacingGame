//
// Created by wildepic on 15/06/2026.
//

#include "gameManager.h"

#include <stdlib.h>

#include "autoSaveMapDevMode.h"
#include "finishMark.h"
#include "gameOverlayText.h"
#include "highscoreManager.h"
#include "initTextures.h"
#include "mapManager.h"
#include "playerCarManager.h"
#include "state.h"

//Runs on every frame
void whilePlaying(Vector2 *playerPos, Camera2D *camera) {
    //Loads autosaved map in dev mode
    if (isDev) {
        readMap();
    }
    //Draws The Map
    drawMap(playerPos);
    playerCar(playerPos, camera);
    timer();

    if (finishMarkPass(playerPos)) {
        if (currentRound < 3) {
            currentRound++;
        }
        else {
            autosaveHighscore();
            loadHighScore();
            gameState = GAME_OVER;
        }
    }
}

//Runs every frame when the gameState is Gameover
void gameOver() {

}

//Runs on init game
void initGame() {
    //Inits the Game Textures
    initTextures();
    mapStringParser();
    loadHighScore();
}
