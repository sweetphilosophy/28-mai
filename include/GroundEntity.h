#pragma once

#include "raylib.h"
#include "Entity.h"
#include "DimensionManager.h"

struct GroundEntity : public Entity {
protected:
    void Jump();
    void ApplyGravity(const Dimension& currentDimension, float deltaTime);
    
    float verticalVelocity = 0.0f;

public:
    void Update(Dimension& currentDimension, float deltaTime) override;
};