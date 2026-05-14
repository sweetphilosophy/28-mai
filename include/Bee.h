#pragma once

#include "raylib.h"
#include "Entity.h"
#include "DimensionManager.h"
#include "Player.h"

class Bee : public Entity {
private:
    // TODO: Trigger distance for chasing vs wandering
    float chasingDetectionRange;
    
    // TODO: Size of the fixed coordinate box for wandering behavior
    Rectangle wanderingBoundingBox;
    
    // TODO: Movement speeds for different states
    float chasingSpeed;
    float wanderingSpeed;
    
    // State management
    bool isChasing = false;
    Vector2 targetPosition;
    float bobbleTimer = 0.0f;
    
    // TODO: Bobble animation parameters (up/down, left/right)
    float bobbleAmplitude;
    float bobbleFrequency;

public:
    Bee(Vector2 position, int dimensionId);
    
    void Update(Dimension& currentDimension, float deltaTime) override;
    void Draw() const override;
    void DrawDebug(const DimensionManager& dimManager) const override;

private:
    // TODO: Implement Matrix Lee's pathfinding algorithm for chasing
    void ChasingBehavior(const Player& player, const Dimension& currentDimension, float deltaTime);
    
    // TODO: Implement wandering behavior with random tile selection in bounding box
    void WanderingBehavior(const Dimension& currentDimension, float deltaTime);
    
    // TODO: Determine texture/sprite for the Bee
    void DrawBee() const;
};
