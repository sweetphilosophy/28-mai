#pragma once

#include <utility>
#include "GroundEntity.h"

class Player : public GroundEntity {
private:
    void HandleMovementInput(const Dimension& currentDimension);
    void HandleMouseInput(Dimension& currentDimension);
    std::pair<int, int> ToIndex(Vector2 mousePos);

public:
    void Input(DimensionManager& dimManager);
};
