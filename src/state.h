#ifndef RACINGGAME_STATE_H
#define RACINGGAME_STATE_H

//Definition GameState
typedef enum GameState {
    PLAYING,
    GAME_OVER,
    MAIN_MENU,
    INIT_ERROR
} GameState;

extern GameState gameState;

#endif // RACINGGAME_STATE_H