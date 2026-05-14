#pragma once

#include "raylib.h"
#include "Player.h"
#include "Bee.h"
#include "DimensionManager.h"
#include <vector>
#include <memory>

struct ObjectManager {

    ObjectManager();

    void Input(DimensionManager& dimManager, CameraManager& cameraManager);
    void Update(DimensionManager& dimManager, CameraManager& cameraManager, float dt);
    void Draw(DimensionManager& dimManager) const;
    void DrawDebug(const DimensionManager& dimManager) const;

    Player player;
    std::vector<std::unique_ptr<Entity>> entities;
};