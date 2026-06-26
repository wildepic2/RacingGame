//
// Created by wildepic on 15/06/2026.
//

#include "gameManager.h"

#include <stdlib.h>

#include "autoSaveMapDevMode.h"
#include "initTextures.h"
#include "playerCarManager.h"
#include "mapManager.h"
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
}

//Runs every frame when the gameState is Gameover
void gameOver() {
}

//Runs on init game
void initGame() {
    //Inits the Game Textures
    initTextures();
    mapStringParser();
}
