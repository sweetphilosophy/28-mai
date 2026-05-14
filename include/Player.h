#pragma once

#include <utility>
#include "GroundEntity.h"
#include "CameraManager.h"
#include "Config.h"
#include <string.h>

class Player : public GroundEntity {
private:
    void HandleMovementInput(const Dimension& currentDimension);
    void HandleMouseInput(Dimension& currentDimension, CameraManager& cameraManager);
    void HandleSaveMapInput(Dimension& currentDimension);
    std::pair<int, int> ToIndex(Vector2 mousePos);

    // for level editor / creative mode
    int currentTilePlaceID = TileIndex::Dirt; // Initialize with a default tile ID
    bool creativeMode = false;
    std::string lastSavedMapName = "";

public:
    int maxHealth = 100;
    int currentHealth = 100;

    void Input(DimensionManager& dimManager, CameraManager& cameraManager);
    void DrawDebug(const DimensionManager& dimManager) const override;
    void DrawHandling_CreativeModeUI(const DimensionManager& dimManager) const;
};
