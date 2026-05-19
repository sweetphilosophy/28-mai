#include "Player.h"
#include "raylib.h"
#include "DimensionManager.h"
#include <ctime> // for saved map filenames
#include <math.h> // for floor and ceil

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

void Player::HandleMouseInput(Dimension& currentDimension, CameraManager& cameraManager) {
    Vector2 mousePos = GetMousePosition();
    mousePos = cameraManager.ScreenToWorld(mousePos);
    std::pair<int, int> tileIndex = ToIndex(mousePos);
    tileIndex.first = currentDimension.WrapX(tileIndex.first);

    Rectangle tileHitbox = hitboxToTileIndexes(currentDimension, hitbox);
    bool mousePointsToPlayer = CheckCollisionPointRec(mousePos, tileHitbox);

    // temporary condition, replace with "debug mode" or "level editor mode" toggle later
    if (!creativeMode) {
        return; // Only allow instant tile placement in creative mode
    }

    if (GetMouseWheelMove() > 0) { // Scroll up to cycle through tile types
        currentTilePlaceID = (currentTilePlaceID + 1) % TileIndex::TileCount; // Cycle through tile IDs
    } else if (GetMouseWheelMove() < 0) { // Scroll down to cycle backwards
        currentTilePlaceID = (currentTilePlaceID - 1 + TileIndex::TileCount) % TileIndex::TileCount; // Cycle backwards through tile IDs
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !mousePointsToPlayer) {

        if (!mouseInPlayerReach(mousePos)) {
            return; // Don't allow interaction if the mouse is too far from the player
        }

        // Enqueue an action to change the tile at tileIndex to a new tile ID (e.g., Air)
        Action action = {tileIndex, TileIndex::Air};
        currentDimension.updateQueue.push(action);
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !mousePointsToPlayer) {
        
        if (!mouseInPlayerReach(mousePos)) {
            return; // Don't allow interaction if the mouse is too far from the player
        }

        // Enqueue an action to change the tile at tileIndex to a new tile ID (e.g., Dirt)
        Action action = {tileIndex, currentTilePlaceID};
        currentDimension.updateQueue.push(action);
    }

    // TODO: attack enemy logic
}

bool Player::mouseInPlayerReach(Vector2 mousePos) {
    // Get player coordinates in world space
    Vector2 playerWorldPos = {hitbox.x + hitbox.width / 2, hitbox.y + hitbox.height / 2};

    int playerMouseDistanceIndexX = abs(playerWorldPos.x - mousePos.x) / tileWidth;
    int playerMouseDistanceIndexY = abs(playerWorldPos.y - mousePos.y) / tileHeight;

    int totalDistanceIndex = playerMouseDistanceIndexX + playerMouseDistanceIndexY;

    return (totalDistanceIndex <= playerReach);
}

void Player::HandleSaveMapInput(Dimension& currentDimension) {
    if (IsKeyPressed(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL)) {
        std::time_t currentTime = std::time(nullptr);
        std::string filename = std::string(saveDirectory) + "\\saved_map_" + std::to_string(currentTime) + ".png";
        currentDimension.SaveToFile(filename);
        lastSavedMapName = filename;
    }
}

void Player::Input(DimensionManager& dimManager, CameraManager& cameraManager) {
    Dimension& currentDimension = dimManager.GetCurrentDimension();
    HandleMovementInput(currentDimension);
    HandleMouseInput(currentDimension, cameraManager);
    HandleSaveMapInput(currentDimension);

    if (IsKeyPressed(KEY_C)) {
        creativeMode = !creativeMode;
    }
}

void Player::Draw(const DimensionManager& dimManager) const {
    DrawDebug(dimManager); // temporary, replace with actual texture draw logic once implemented
}

void Player::DrawDebug(const DimensionManager& dimManager) const {
    // Draw rectangle outline for debugging using raylib function
    DrawRectangleLinesEx(hitbox, 2, RED);
}

void Player::DrawHandling_CreativeModeUI(const DimensionManager& dimManager) const {
    const Dimension& currentDimension = dimManager.GetCurrentDimension();
    
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

Rectangle Player::hitboxToTileIndexes(const Dimension& currentDimension, const Rectangle& hitbox) {
    // Calculate the tile indexes that the hitbox occupies
    // By doing this, we "snap" the hitbox to the tile grid
    float leftTile = hitbox.x / tileWidth;
    float rightTile = (hitbox.x + hitbox.width) / tileWidth;
    float topTile = hitbox.y / tileHeight;
    float bottomTile = (hitbox.y + hitbox.height) / tileHeight;

    leftTile = floor(leftTile); // snap to left if in between
    rightTile = ceil(rightTile); // snap to right if in between
    topTile = floor(topTile); // snap to top if in between
    bottomTile = ceil(bottomTile); // snap to bottom if in between

    // Extend the hitbox to snap to the tile grid
    leftTile = currentDimension.WrapX(leftTile);
    rightTile = currentDimension.WrapX(rightTile);

    // top left corner, width, height
    return {leftTile, topTile, rightTile - leftTile, bottomTile - topTile};
}