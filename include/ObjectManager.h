#pragma once

#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "DimensionManager.h"
#include <vector>
#include <memory> // to avoid slicing when storing Enemy objects in a vector

struct ObjectManager {

    ObjectManager();

    void Input(DimensionManager& dimManager, CameraManager& cameraManager);
    void Update(DimensionManager& dimManager, CameraManager& cameraManager, float dt);
    void Draw(DimensionManager& dimManager) const;

    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;

private:    
    // placeholder functions (for now)
    void HandlePlayerEntityInteractions(Dimension& currentDimension);
    void HandleEntitySpawning(Dimension& currentDimension);
    void HandleEntityDespawning(Dimension& currentDimension, const CameraManager& cameraManager);
    bool ShouldUpdateRandomEntityAction(float dt);
};