//
// Created by wildepic on 15/06/2026.
//

#include "raylib.h"

#include "gameManager.h"

#include "initTextures.h"
#include "state.h"

//Runs on every frame
void whilePlaying() {}
//Runs every frame when the gameState is Gameover
void gameOver() {}
//Runs on init game
void initGame() {
    //Inits the Game Textures
    initTextures();
}
