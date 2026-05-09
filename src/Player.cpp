#include "Player.h"
#include "raylib.h"
#include "DimensionManager.h"
#include <ctime> // for saved map filenames

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

    if (IsKeyPressed(KEY_C)) {
        creativeMode = !creativeMode;
    }

    // temporary condition, replace with "debug mode" or "level editor mode" toggle later
    if (!creativeMode) {
        return; // Only allow instant tile placement in creative mode
    }

    if (GetMouseWheelMove() > 0) { // Scroll up to cycle through tile types
        currentTilePlaceID = (currentTilePlaceID + 1) % TileIndex::TileCount; // Cycle through tile IDs
    } else if (GetMouseWheelMove() < 0) { // Scroll down to cycle backwards
        currentTilePlaceID = (currentTilePlaceID - 1 + TileIndex::TileCount) % TileIndex::TileCount; // Cycle backwards through tile IDs
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Enqueue an action to change the tile at tileIndex to a new tile ID (e.g., Air)
        Action action = {tileIndex, TileIndex::Air};
        currentDimension.updateQueue.push(action);
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        // Enqueue an action to change the tile at tileIndex to a new tile ID (e.g., Dirt)
        Action action = {tileIndex, currentTilePlaceID};
        currentDimension.updateQueue.push(action);
    }
}

void Player::HandleSaveMapInput(Dimension& currentDimension) {
    if (IsKeyPressed(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL)) {
        std::time_t currentTime = std::time(nullptr);
        std::string filename = std::string(saveDirectory) + "\\saved_map_" + std::to_string(currentTime) + ".png";
        currentDimension.SaveToFile(filename);
        lastSavedMapName = filename;
    }
}

void Player::Input(DimensionManager& dimManager) {
    Dimension& currentDimension = dimManager.GetCurrentDimension();
    HandleMovementInput(currentDimension);
    HandleMouseInput(currentDimension);
    HandleSaveMapInput(currentDimension);
}

void Player::DrawDebug(const DimensionManager& dimManager) const {
    const Dimension& currentDimension = dimManager.GetCurrentDimension();
    DrawRectangleLinesEx(hitbox, 2, RED);
    if (creativeMode) {
        DrawText(TextFormat("Current Tile ID: %s", currentDimension.GetNameFromID(currentTilePlaceID)), 10, 10, 20, BLACK);
        if (!lastSavedMapName.empty()) {
            DrawText(TextFormat("Last Saved Map: %s", lastSavedMapName.c_str()), 10, 40, 20, BLACK);
        } else {
            DrawText("Last Saved Map: None", 10, 40, 20, BLACK);
        }
        DrawText("Left Click: Place Air | Right Click: Place Current Tile", 10, 70, 20, BLACK);
        DrawText("Mouse Wheel: Cycle Tile Type", 10, 100, 20, BLACK);
        DrawText("Press Ctrl+S to Save Current Map", 10, 130, 20, BLACK);
    }
}