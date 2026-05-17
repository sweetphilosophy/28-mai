#pragma once

#include "raylib.h"
#include "Enemy.h"
#include "DimensionManager.h"
#include "Player.h"

class Bee : public Enemy {
private:

    float bobbleTimer = 0.0f;
    
    float bobbleAmplitude;
    float bobbleFrequency;

    void DrawVectorBee() const;

    // TODO: Implement Matrix Lee's pathfinding algorithm for chasing
    void HandleChasing(const Player* player) override;
    
    // TODO: add collision avoidance in wandering behavior or say "the bee as a drill" and make it break tiles
    void HandleWondering() override;

    void ApplyWobble(float deltaTime);

public:
    Bee(Vector2 position, int dimensionId);

    void Draw() const override;
    void DrawDebug(const DimensionManager& dimManager) const override;
    void Update(Dimension& currentDimension, float deltaTime, const Player* player) override;
};
