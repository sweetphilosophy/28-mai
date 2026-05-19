#pragma once

#include "raylib.h"
#include "DimensionManager.h"
#include "Entity.h"

struct Entity;
struct Dimension;

struct GroundEntity : public Entity {
protected:
    void Jump();
    void ApplyGravity(const Dimension& currentDimension, float deltaTime);
    
    float verticalVelocity = 0.0f;

public:
    virtual void Update(Dimension& currentDimension, float deltaTime);
};