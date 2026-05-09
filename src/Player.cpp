#include "Player.h"
#include "raylib.h"
#include "Config.h"
#include "DimensionManager.h"

std::pair<int, int> Player::ToIndex(Vector2 mousePos) {
    int tileX = mousePos.x / tileWidth;
    int tileY = mousePos.y / tileHeight;
    return {tileX, tileY};
}

void Player::HandleMovementInput(const Dimension& currentDimension) {
    
    if (IsKeyDown(KEY_SPACE) && !isJumping) {
        Jump();
    }

    bool rightPressed = IsKeyDown(KEY_D);
    bool leftPressed = IsKeyDown(KEY_A);

    static bool wasRightPressed = false;

    if (!rightPressed && !leftPressed) { // no horizontal movement
        movementUnitVector.x = 0.0f;
    }
    if (leftPressed && !rightPressed) { // left only
        movementUnitVector.x = -1.0f;
        wasRightPressed = false;
    }
    if (rightPressed && !leftPressed) { // right only
        movementUnitVector.x = 1.0f;
        wasRightPressed = true;
    }
    // if both are pressed, we override the direction with the new press
    if (rightPressed && leftPressed) {
        movementUnitVector.x = wasRightPressed ? -1.0f : 1.0f; // invert the previous direction
    }
}

void Player::HandleMouseInput(Dimension& currentDimension) {
    Vector2 mousePos = GetMousePosition();
    std::pair<int, int> tileIndex = ToIndex(mousePos);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Enqueue an action to change the tile at tileIndex to a new tile ID (e.g., Air)
        Action action = {tileIndex, TileIndex::Air};
        currentDimension.updateQueue.push(action);
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        // Enqueue an action to change the tile at tileIndex to a new tile ID (e.g., Dirt)
        Action action = {tileIndex, TileIndex::Dirt};
        currentDimension.updateQueue.push(action);
    }
}

void Player::Input(DimensionManager& dimManager) {
    Dimension& currentDimension = dimManager.GetCurrentDimension();
    HandleMovementInput(currentDimension);
    HandleMouseInput(currentDimension);
}
