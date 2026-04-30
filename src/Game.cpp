#include "Game.h"

void Game::run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Starter Template");
    SetTargetFPS(60);

    handleDimensions.dimensions.emplace_back("assets\\misc\\Dimension0.png");

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

    handleDimensions.Draw_MapDebug();

    EndDrawing();
}