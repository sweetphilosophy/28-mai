#pragma once

#include <utility>
#include "GroundEntity.h"
#include "CameraManager.h"
#include "Config.h"
#include <string.h>

class CameraManager; // Forward declaration to avoid circular dependency
struct Dimension; // Forward declaration to avoid circular dependency
struct DimensionManager; // Forward declaration to avoid circular dependency

struct Player : public GroundEntity {
private:
    void HandleMovementInput(const Dimension& currentDimension);
    void HandleMouseInput(Dimension& currentDimension, CameraManager& cameraManager);
    void HandleSaveMapInput(Dimension& currentDimension);
    std::pair<int, int> ToIndex(Vector2 mousePos);

    // for level editor / creative mode
    int currentTilePlaceID = TileIndex::Dirt; // Initialize with a default tile ID
    bool creativeMode = false;
    std::string lastSavedMapName = "";
    Rectangle hitboxToTileIndexes(const Dimension& currentDimension, const Rectangle& hitbox); // extend and snap the hibox to the tile grid, aka returning the tiles where the hitbox is located  

public:
    int maxHealth = 100;
    int currentHealth = 100;

    void Input(DimensionManager& dimManager, CameraManager& cameraManager);
    void DrawDebug(const DimensionManager& dimManager) const override;
    // Placeholder for now, implement with animations using texture manager later
    void Draw(const DimensionManager& dimManager) const;
    void DrawHandling_CreativeModeUI(const DimensionManager& dimManager) const;
};
