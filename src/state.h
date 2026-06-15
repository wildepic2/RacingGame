#ifndef RACINGGAME_STATE_H
#define RACINGGAME_STATE_H

typedef enum GameState {
    PLAYING,
    GAME_OVER,
    MAIN_MENU
} GameState;

extern GameState gameState;

#endif // RACINGGAME_STATE_H