#include "gameManager.h"
#include "raylib.h"
#include "state.h"
#include "menuManager.h"

int main(void)
{
    //Sets Window Size
    const int screenWidth = 800;
    const int screenHeight = 800;
    //Inits the window
    InitWindow(screenWidth, screenHeight, "Racing Game");
    SetTargetFPS(60);
    //Inits the game looking
    initGame();
    //Windows is open as long as you dont close it
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //Switches between the game states
        switch (gameState) {
            case MAIN_MENU:
                displayMainMenu();
                break;
            case PLAYING:
                whilePlaying();
                break;
            case GAME_OVER:
                gameOver();
                displayGameoverMenu();
                break;
            case INIT_ERROR:
                break;
        }

        EndDrawing();
    }
    //Fully closes the window
    CloseWindow();
    return 0;
}
