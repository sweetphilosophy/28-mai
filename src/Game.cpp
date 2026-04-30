#include "Game.h"

void Game::RunGame() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Starter Template");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Input(dt);
        Update(dt);
        Draw();
    }
    CloseWindow();
}

void Game::Input(float dt) {
    // Handle user input here
}

void Game::Update(float dt) {
    // Update game logic here
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw game elements here
    DrawText("Hello, Raylib!", 10, 10, 20, DARKGRAY);

    EndDrawing();
}