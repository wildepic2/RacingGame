#include "gameManager.h"
#include "raylib.h"
#include "state.h"
#include "menuManager.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Racing Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        initGame();

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
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
