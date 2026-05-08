#include "GroundEntity.h"
#include "Config.h"
#include <cmath>

void GroundEntity::Jump() {
    if (!isJumping) {
        isJumping = true;
        verticalVelocity = jumpVelocity;
    }
}

void GroundEntity::ApplyGravity(const Dimension& currentDimension, float deltaTime) {
    verticalVelocity += gravity * deltaTime; // Gravity acceleration
}

void GroundEntity::Update(Dimension& currentDimension, float deltaTime) {
    ApplyGravity(currentDimension, deltaTime);

    // Horizontal movement first
    float nextX = hitbox.x + movementUnitVector.x * speed * deltaTime;
    Rectangle xBox = hitbox;
    xBox.x = nextX;

    bool x_hitsSolidTile = RectangleHitsSolidTile(currentDimension, xBox);

    if (x_hitsSolidTile) {
        SnapToSideTile(currentDimension, nextX, movementUnitVector.x > 0);
    } else {
        hitbox.x = nextX;
    }
    
    // Vertical movement second
    float nextY = hitbox.y + verticalVelocity * deltaTime;
    Rectangle nextHitbox = hitbox;
    nextHitbox.y = nextY;

    bool y_hitsSolidTile = RectangleHitsSolidTile(currentDimension, nextHitbox);
    bool movingDown = verticalVelocity >= 0.0f;


    if (movingDown) {
        if (y_hitsSolidTile) { // landed on the ground
            hitbox.y = nextY;
            SnapToGround(currentDimension);
            verticalVelocity = 0.0f; // stop falling
            isJumping = false;
        } else { // let the entity fall
            hitbox.y = nextY;
            isJumping = true;
        }
    } else { // moving up
        if (y_hitsSolidTile) { // hit a solid tile above
            verticalVelocity = 0.0f;
        } else {
            hitbox.y = nextY;
        }
    }

}
