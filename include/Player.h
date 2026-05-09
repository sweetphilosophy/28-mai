#pragma once

#include <utility>
#include "GroundEntity.h"
#include "Config.h"
#include <string.h>

class Player : public GroundEntity {
private:
    void HandleMovementInput(const Dimension& currentDimension);
    void HandleMouseInput(Dimension& currentDimension);
    void HandleSaveMapInput(Dimension& currentDimension);
    std::pair<int, int> ToIndex(Vector2 mousePos);

    // for level editor / creative mode
    int currentTilePlaceID = TileIndex::Dirt; // Initialize with a default tile ID
    bool creativeMode = false;
    std::string lastSavedMapName = "";

public:
    void Input(DimensionManager& dimManager);
    void DrawDebug(const DimensionManager& dimManager) const override;
};
