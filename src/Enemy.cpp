#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 position, int dimensionId) {
    hitbox = {position.x, position.y, tileWidth, tileHeight}; // Default entity size, can be overridden by specific enemy types
    this->dimensionID = dimensionId;
    this->entityID = EntityID::NONE; // Default entity ID for generic enemies, can be overridden by specific enemy types
}

void Enemy::Update(Dimension& currentDimension, float deltaTime) {
    // Default update when no Player pointer is provided — forward to overload with nullptr
    Update(currentDimension, deltaTime, nullptr);
}

void Enemy::Update(Dimension& currentDimension, float deltaTime, const Player* player) {
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

    bool reachedTarget = PointToTarget();
    if (isRebounding && reachedTarget) {
        isRebounding = false;
    }
    
    // Update position based on movement vector
    hitbox.x += movementUnitVector.x * speed * deltaTime;
    hitbox.y += movementUnitVector.y * speed * deltaTime;
}

void Enemy::HandleChasing(const Player* player) {
    
    if (!player) {
        static bool warningLogged = false;
        if (!warningLogged) {
            TraceLog(LOG_WARNING, "HandleChasing called without player reference, skipping chasing logic");
            warningLogged = true;
        }
        return;
    }
    
    if (!isChasing) return;
    if (isRebounding) return; 

    speed = chasingSpeed;

    // centre of player hitbox
    targetPosition = {player->hitbox.x + player->hitbox.width/2, player->hitbox.y + player->hitbox.height/2}; // Chase the player's center position

}

void Enemy::HandleRebounding() {
    if (!isRebounding) return;

    speed = chasingSpeed; // Use chasing speed for rebounding movement
    // target position remains the same

    // can later add small bobble etc. to make it less predictable and more natural
}

void Enemy::HandleWondering() {
    
    if (isChasing) return;
    if (isRebounding) return; 
    
    speed = wanderingSpeed;
    
}

void Enemy::UpdateIsChasing(const Player* player) {
    
    // Check if player is within chasing detection range
    Vector2 enemyCenter = {hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2};
    Vector2 playerCenter = {player->hitbox.x + player->hitbox.width/2, player->hitbox.y + player->hitbox.height/2};
    float distanceToPlayer = Vector2Distance(enemyCenter, playerCenter);
    
    wasChasing = isChasing; // Store previous chasing state for rebound logic
    isChasing = (distanceToPlayer <= chasingDetectionRange);

    // Start rebounding if we just lost the player
    // Allow reset to isRebounding = false only from HandleChasing
    isRebounding = (wasChasing && !isChasing) || (isRebounding && !isChasing); 
}

bool Enemy::PointToTarget() {
    
    // Move towards targetPosition
    Vector2 enemyCenter = {hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2};
    Vector2 direction = Vector2Subtract(targetPosition, enemyCenter);
    float distance = Vector2Length(direction);

    if (distance <= 0.5f) { // Threshold to consider "reached" the last known position
        movementUnitVector = {0, 0};
        return true; // Target reached
    }

    movementUnitVector = Vector2Scale(direction, 1.0f / distance);
    return false; // Target not reached
}