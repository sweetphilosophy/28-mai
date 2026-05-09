#pragma once

#include "raylib.h"
#include "DimensionManager.h"
#include "ObjectManager.h"
#include "Config.h"
#include "CameraManager.h"

class Game {
private:

    void Input(float dt, CameraManager& cameraManager);
    void Update(float dt, CameraManager& cameraManager);
    void Draw();

    void InitGameWindow();
    void InitGameCamera();
    void HandleFullscreenToggle();

    DimensionManager dimensionManager;
    ObjectManager objectManager;
    CameraManager cameraManager;
public:
    void run();
    Game();
};