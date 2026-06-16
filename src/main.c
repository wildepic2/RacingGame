#include "gameManager.h"
#include "raylib.h"
#include "state.h"
#include "menuManager.h"

int main(void) {
    //Inits Variables for Car Pos and Rotation
    Vector2 playerPosition = {375, 375};
    float playerRotation = 0;
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
                gameState = PLAYING;
                break;
            case PLAYING:
                whilePlaying(&playerPosition, &playerRotation);
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
