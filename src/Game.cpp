#include "Game.h"
#include "Config.h"
#include <algorithm> // added

Game::Game() {

    // should be a single active dimension at once
    // active dimension is the one that is drawn and updated
    // inactive dimensions are just stored in memory and can be switched to

    dimensionManager.dimensions.emplace_back("assets\\misc\\Dimension0.png", SetToActiveDimension);
}

void Game::run() {

    InitGameWindow();
    InitGameCamera();
    textureManager.Init(); // must load textures only after window is initialized

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Input(dt, cameraManager);
        Update(dt, cameraManager);
        Draw();
    }

    CloseWindow();
}

void Game::Input(float dt, CameraManager& cameraManager) {
    HandleFullscreenToggle();
    objectManager.Input(dimensionManager, cameraManager);
    inventory.HandleInput();
}

void Game::Update(float dt, CameraManager& cameraManager) {
    objectManager.Update(dimensionManager, cameraManager, dt);
    dimensionManager.Update();
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(cameraManager.GetCamera());
    // draw things that exist in the world regardless of camera view

    dimensionManager.Draw(cameraManager, textureManager);
    objectManager.Draw(dimensionManager);

    EndMode2D();

    
    objectManager.player.DrawHandling_CreativeModeUI(dimensionManager);
    inventory.Draw();
    // Draw HP bar
    int barWidth = 200;
    int barHeight = 15;
    int barX = GetScreenWidth() - barWidth - 20;
    int barY = 20;
    DrawRectangle(barX, barY, barWidth, barHeight, RED); // background
    float healthRatio = (float)objectManager.player.currentHealth / objectManager.player.maxHealth;
    DrawRectangle(barX, barY, (int)(barWidth * healthRatio), barHeight, GREEN); // fill
    DrawRectangleLines(barX, barY, barWidth, barHeight, BLACK); // border
    DrawText(TextFormat("HP: %d/%d", objectManager.player.currentHealth, objectManager.player.maxHealth), barX, barY + barHeight + 5, 16, BLACK);
    // Draw UI elements here if needed
    // aka things that exist directly in screen space

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

void Game::InitGameCamera() {
    cameraManager.Init(GetScreenWidth(), GetScreenHeight());
    cameraManager.RebuildVerticalLimits(dimensionManager.GetCurrentDimension());
    cameraManager.UpdateFollow(objectManager.player.hitbox, dimensionManager.GetCurrentDimension());
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
        // Update camera viewport and recompute limits after any fullscreen toggle
        cameraManager.SetViewport(GetScreenWidth(), GetScreenHeight());
        cameraManager.RebuildVerticalLimits(dimensionManager.GetCurrentDimension());
    }
}