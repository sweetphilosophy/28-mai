#include "Bee.h"
#include "Config.h"
#include "Player.h"
#include "raymath.h" // for Vector2 operations
#include <cmath>

Bee::Bee(Vector2 position, int dimensionId) : Enemy(position, dimensionId) {
    hitbox = {position.x, position.y, tileWidth, tileHeight}; // Bee sprite dimensions
    this->entityID = EntityID::BEE;

    // Set HP and damage values
    hp = beeHP;
    damagePerHit = beeDamagePerHit;
    
    // Set speed values for chasing and wandering
    chasingSpeed = beeChasingSpeed;
    wanderingSpeed = beeWanderingSpeed;
    
    // Set chasing detection range
    chasingDetectionRange = beeChasingDetectionRange;
    
    // Set wandering bounding box (X by Y pixels around spawn position)
    wanderingBoundingBox = {position.x - beeWanderingBoundingBoxX / 2, // Center the bounding box around the initial position
                            position.y - beeWanderingBoundingBoxY / 2, 
                            beeWanderingBoundingBoxX, 
                            beeWanderingBoundingBoxY};
    
    // Set bobble animation parameters
    bobbleAmplitude = beeBobbleAmplitude;
    bobbleFrequency = beeBobbleFrequency;
}

void Bee::Draw() const {
    DrawVectorBee(); // temporary vector shape draw, replace with texture draw logic once implemented
}

void Bee::DrawDebug(const DimensionManager& dimManager) const {
    // Draw hitbox
    DrawRectangleLines(
        (int)hitbox.x, (int)hitbox.y,
        (int)hitbox.width, (int)hitbox.height,
        LIME
    );
    
    if (isChasing) {
        // Draw chase target
        DrawCircleLines((int)targetPosition.x, (int)targetPosition.y, 5, RED);
    }
    if (isRebounding) {
        // Draw rebound target
        DrawCircleLines((int)targetPosition.x, (int)targetPosition.y, 5, ORANGE);
    }
    if (!isChasing && !isRebounding) {
        // Draw target in bounding box
        DrawCircleLines((int)targetPosition.x, (int)targetPosition.y, 5, RED);
        // Draw wandering bounding box
        DrawRectangleLinesEx(wanderingBoundingBox, 2, BLUE);
    }

    DrawCircleLinesV(Vector2({hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2}), chasingDetectionRange, GREEN);
    
    // Draw the bee itself on top for visibility
    DrawVectorBee();
}

void Bee::HandleWondering() {
    
    if (isChasing) return;
    if (isRebounding) return;
    
    speed = wanderingSpeed;
    
    // Check if we need a new target (first time or reached current target)
    Vector2 beeCenter = {hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2};
    if (Vector2Distance(beeCenter, targetPosition) < 10.0f || (targetPosition.x == 0 && targetPosition.y == 0)) {
        // Pick new random target within bounding box
        float randomX = wanderingBoundingBox.x + (float)GetRandomValue(0, (int)wanderingBoundingBox.width);
        float randomY = wanderingBoundingBox.y + (float)GetRandomValue(0, (int)wanderingBoundingBox.height);
        targetPosition = {randomX, randomY};
    }
}

void Bee::DrawVectorBee() const {
    
    // For now, placeholder yellow circle with black outline - make it bigger and more visible
    DrawCircle((int)(hitbox.x + hitbox.width/2), (int)(hitbox.y + hitbox.height/2), 12, YELLOW);
    DrawCircleLines((int)(hitbox.x + hitbox.width/2), (int)(hitbox.y + hitbox.height/2), 12, BLACK);
    
    // Add some wings for bee appearance
    DrawCircle((int)(hitbox.x + hitbox.width/2 - 6), (int)(hitbox.y + hitbox.height/2 - 4), 4, WHITE);
    DrawCircle((int)(hitbox.x + hitbox.width/2 + 6), (int)(hitbox.y + hitbox.height/2 - 4), 4, WHITE);
}

void Bee::ApplyWobble(float deltaTime) {
    // Apply bobble animation
    bobbleTimer += deltaTime;
    float bobbleOffsetX = sinf(bobbleTimer * bobbleFrequency) * bobbleAmplitude * 0.3f;
    float bobbleOffsetY = cosf(bobbleTimer * bobbleFrequency * 1.5f) * bobbleAmplitude;
    
    // Add bobble to movement
    movementUnitVector.x += bobbleOffsetX * deltaTime;
    movementUnitVector.y += bobbleOffsetY * deltaTime;
    
    // Normalize movement vector to maintain consistent speed
    float movementLength = Vector2Length(movementUnitVector);
    if (movementLength > 0) {
        movementUnitVector = Vector2Scale(movementUnitVector, 1.0f / movementLength);
    }
}

// Bee-specific overrides
void Bee::Update(Dimension& currentDimension, float deltaTime, const Player* player) {
    
    if (player) {
        UpdateIsChasing(player);
    } else {
        static bool warningLogged = false;
        isChasing = false;

        if (!warningLogged) {
            TraceLog(LOG_WARNING, "Enemy Update called without player reference, defaulting to non-chasing behavior");
            warningLogged = true;
        }
    }

    HandleWondering();
    HandleChasing(player);
    HandleRebounding();

    ApplyWobble(deltaTime);

    bool reachedTarget = PointToTarget();
    if (isRebounding && reachedTarget) {
        isRebounding = false;
    }

    // Update position based on movement vector
    hitbox.x += movementUnitVector.x * speed * deltaTime;
    hitbox.y += movementUnitVector.y * speed * deltaTime;
    
}

void Bee::HandleChasing(const Player* player) {
    // For now, reuse the generic enemy chasing behaviour
    Enemy::HandleChasing(player);
}