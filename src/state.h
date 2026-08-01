#ifndef RACINGGAME_STATE_H
#define RACINGGAME_STATE_H

//Definition GameState
typedef enum GameState {
    PLAYING,
    GAME_OVER,
    MAIN_MENU,
    ERROR_STATE
} GameState;

extern GameState gameState;
extern bool isDev;

extern int stoppWatchTime;
extern int currentRound;
extern int highscore;

#endif // RACINGGAME_STATE_H
