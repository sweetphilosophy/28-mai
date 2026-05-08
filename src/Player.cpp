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
    movementUnitVector.x = 0;

    if (IsKeyDown(KEY_D)) {
        movementUnitVector.x = 1;
    }
    if (IsKeyDown(KEY_A)) {
        movementUnitVector.x = -1;
    }
    if (IsKeyDown(KEY_SPACE) && !isJumping) {
        Jump();
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
