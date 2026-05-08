#include "Game.h"

Game::Game() {

    dimensionManager.dimensions.emplace_back("assets\\misc\\Dimension0.png", true);
}

void Game::run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Starter Template");
    SetTargetFPS(targetFPS);

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
    objectManager.Input(dimensionManager);
}

void Game::Update(float dt) {
    objectManager.Update(dimensionManager, dt);
    dimensionManager.Update();
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    dimensionManager.Draw_MapDebug();
    objectManager.Draw();

    EndDrawing();
}