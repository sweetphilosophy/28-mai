#include "Game.h"
#include "Config.h"
#include <algorithm> // added

Game::Game() {

    // should be a single active dimension at once
    // active dimension is the one that is drawn and updated
    // inactive dimensions are just stored in memory and can be switched to

    dimensionManager.dimensions.emplace_back("assets\\misc\\Dimension0.png", isActiveDimension);
}

void Game::run() {

    InitGameWindow();

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
    HandleFullscreenToggle();
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
    objectManager.Draw(dimensionManager);

    EndDrawing();
}

void Game::InitGameWindow() {
    // ensure initial window fits the monitor
    int monitorW = GetMonitorWidth(0);
    int monitorH = GetMonitorHeight(0);
    int initW = std::min(SCREEN_WIDTH, monitorW);
    int initH = std::min(SCREEN_HEIGHT, monitorH);

    InitWindow(initW, initH, "Raylib Starter Template");
    SetTargetFPS(targetFPS);

    // if monitor is 1080p start fullscreen
    if (monitorH == 1080) ToggleFullscreen();

    // ensure window is centered / titlebar visible in windowed mode
    if (!IsWindowFullscreen()) {
        int w = GetScreenWidth();
        int h = GetScreenHeight();
        int posX = std::max(0, (monitorW - w) / 2);
        int posY = std::max(0, (monitorH - h) / 2);
        SetWindowPosition(posX, posY);
    }
}

void Game::HandleFullscreenToggle() {
    // Toggle fullscreen with F11 and keep windowed mode visible and bounded
    if (IsKeyPressed(KEY_F11)) {
        bool wasFullscreen = IsWindowFullscreen();
        ToggleFullscreen();

        // if we just exited fullscreen (wasFullscreen == true) adjust size/position
        if (wasFullscreen) {
            int mW = GetMonitorWidth(0);
            int mH = GetMonitorHeight(0);
            int w = GetScreenWidth();
            int h = GetScreenHeight();

            if (w > mW || h > mH) {
                int newW = std::min(w, mW);
                int newH = std::min(h, mH);
                SetWindowSize(newW, newH);
                w = newW; h = newH;
            }

            int posX = std::max(0, (mW - w) / 2);
            int posY = std::max(0, (mH - h) / 2);
            SetWindowPosition(posX, posY);
        }
    }
}