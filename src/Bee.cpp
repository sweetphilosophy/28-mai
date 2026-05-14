#include "Bee.h"
#include "Config.h"
#include "Player.h"
#include <cmath>

// Helper functions for Vector2 operations (since some raylib versions don't have them)
inline float Vector2DistanceCustom(Vector2 v1, Vector2 v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrtf(dx * dx + dy * dy);
}

inline Vector2 Vector2SubtractCustom(Vector2 v1, Vector2 v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

inline float Vector2LengthCustom(Vector2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

inline Vector2 Vector2ScaleCustom(Vector2 v, float scale) {
    return {v.x * scale, v.y * scale};
}

Bee::Bee(Vector2 position, int dimensionId) {
    hitbox = {position.x, position.y, 16.0f, 16.0f}; // Bee sprite dimensions
    this->id = dimensionId;
    
    // Set HP and damage values
    hp = 20;
    damagePerHit = 5;
    
    // Set speed values for chasing and wandering
    chasingSpeed = 80.0f;
    wanderingSpeed = 40.0f;
    
    // Set chasing detection range
    chasingDetectionRange = 150.0f;
    
    // Set wandering bounding box (200x200 pixels around spawn position)
    wanderingBoundingBox = {position.x - 100, position.y - 100, 200, 200};
    
    // Set bobble animation parameters
    bobbleAmplitude = 8.0f;
    bobbleFrequency = 2.0f;
}

void Bee::Update(Dimension& currentDimension, float deltaTime) {
    // For now, just wander. TODO: Implement chasing when player detection is available
    WanderingBehavior(currentDimension, deltaTime);
    
    // Update position based on movement vector
    hitbox.x += movementUnitVector.x * speed * deltaTime;
    hitbox.y += movementUnitVector.y * speed * deltaTime;
    
    // Simple debug: make sure bee stays within reasonable bounds
    if (hitbox.x < 0) hitbox.x = 0;
    if (hitbox.x > 1000) hitbox.x = 1000;
    if (hitbox.y < 0) hitbox.y = 0;
    if (hitbox.y > 1000) hitbox.y = 1000;
}

void Bee::Draw() const {
    DrawBee();
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
}

void Bee::ChasingBehavior(const Player& player, const Dimension& currentDimension, float deltaTime) {
    speed = chasingSpeed;
    
    // Update target to player's position
    targetPosition = {player.hitbox.x + player.hitbox.width/2, player.hitbox.y + player.hitbox.height/2};
    
    // TODO: Implement Matrix Lee's pathfinding algorithm
    // For now, use direct movement towards player
    Vector2 beeCenter = {hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2};
    Vector2 direction = Vector2SubtractCustom(targetPosition, beeCenter);
    float distance = Vector2LengthCustom(direction);
    
    if (distance > 0) {
        movementUnitVector = Vector2ScaleCustom(direction, 1.0f / distance);
    } else {
        movementUnitVector = {0, 0};
    }
}

void Bee::WanderingBehavior(const Dimension& currentDimension, float deltaTime) {
    speed = wanderingSpeed;
    
    // Check if we need a new target (first time or reached current target)
    Vector2 beeCenter = {hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2};
    if (Vector2DistanceCustom(beeCenter, targetPosition) < 10.0f || (targetPosition.x == 0 && targetPosition.y == 0)) {
        // Pick new random target within bounding box
        float randomX = wanderingBoundingBox.x + (float)GetRandomValue(0, (int)wanderingBoundingBox.width);
        float randomY = wanderingBoundingBox.y + (float)GetRandomValue(0, (int)wanderingBoundingBox.height);
        targetPosition = {randomX, randomY};
    }
    
    // Move towards target (simple direct movement for now)
    Vector2 direction = Vector2SubtractCustom(targetPosition, beeCenter);
    float distance = Vector2LengthCustom(direction);
    
    if (distance > 0) {
        movementUnitVector = Vector2ScaleCustom(direction, 1.0f / distance);
    } else {
        movementUnitVector = {0, 0};
    }
    
    // Apply bobble animation
    bobbleTimer += deltaTime;
    float bobbleOffsetX = sinf(bobbleTimer * bobbleFrequency) * bobbleAmplitude * 0.3f;
    float bobbleOffsetY = cosf(bobbleTimer * bobbleFrequency * 1.5f) * bobbleAmplitude;
    
    // Add bobble to movement
    movementUnitVector.x += bobbleOffsetX * deltaTime;
    movementUnitVector.y += bobbleOffsetY * deltaTime;
    
    // Normalize movement vector to maintain consistent speed
    float movementLength = Vector2LengthCustom(movementUnitVector);
    if (movementLength > 0) {
        movementUnitVector = Vector2ScaleCustom(movementUnitVector, 1.0f / movementLength);
    }
}

void Bee::DrawBee() const {
    // TODO: Load and draw bee texture/sprite
    // For now, placeholder yellow circle with black outline - make it bigger and more visible
    DrawCircle((int)(hitbox.x + hitbox.width/2), (int)(hitbox.y + hitbox.height/2), 12, YELLOW);
    DrawCircleLines((int)(hitbox.x + hitbox.width/2), (int)(hitbox.y + hitbox.height/2), 12, BLACK);
    
    // Add some wings for bee appearance
    DrawCircle((int)(hitbox.x + hitbox.width/2 - 6), (int)(hitbox.y + hitbox.height/2 - 4), 4, WHITE);
    DrawCircle((int)(hitbox.x + hitbox.width/2 + 6), (int)(hitbox.y + hitbox.height/2 - 4), 4, WHITE);
}
