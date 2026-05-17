#pragma once

#include "Entity.h"
#include "Player.h"

struct Enemy : public Entity {
public:

    Enemy(Vector2 position, int dimensionID);
    void Update(Dimension& currentDimension, float deltaTime) override;
    virtual void Update(Dimension& currentDimension, float deltaTime, const Player* player);

protected:
    float chasingDetectionRange;
    
    Rectangle wanderingBoundingBox;
    
    float chasingSpeed;
    float wanderingSpeed;
    
    // State management
    bool isChasing = false;
    bool wasChasing = false; // Used for "rebound mechanic" for going to the last known player position 

    bool isRebounding = false; // Whether the enemy is currently moving towards the last known player position after losing sight of the player

    Vector2 targetPosition;

    virtual void UpdateIsChasing(const Player* player);

    // TODO: Implement Matrix Lee's pathfinding algorithm for chasing
    virtual void HandleChasing(const Player* player);

    virtual void HandleRebounding();
    
    // TODO: Implement wandering behavior with random tile selection in bounding box
    virtual void HandleWondering(); // deltaTile for time-based movement

    // does not account for terrain - intended feature
    // return true if reached target position
    bool PointToTarget();
};