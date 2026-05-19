#include "CameraManager.h"
#include "DimensionManager.h"
#include <algorithm>
#include <cmath>
#include "Player.h"

void CameraManager::Init(int screenW, int screenH) {
    camera.target = {0.0f, 0.0f};
    camera.offset = {screenW * 0.5f, screenH * 0.5f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    this->screenW = screenW;
    this->screenH = screenH;
}

void CameraManager::SetViewport(int screenW, int screenH) {
    camera.offset = {screenW * 0.5f, screenH * 0.5f};
    this->screenW = screenW;
    this->screenH = screenH;
}

void CameraManager::RebuildVerticalLimits(const Dimension& dim) {
    int h = dim.getHeight();
    int w = dim.getWidth();

    int firstNonBedrock = 0;
    while (firstNonBedrock < h) {
        bool allBedrock = true;
        for (int x = 0; x < w; ++x) {
            if (dim.tiles[firstNonBedrock][x] != TileIndex::Bedrock) { allBedrock = false; break; }
        }
        if (!allBedrock) break;
        ++firstNonBedrock;
    }

    int lastNonBedrock = h - 1;
    while (lastNonBedrock >= 0) {
        bool allBedrock = true;
        for (int x = 0; x < w; ++x) {
            if (dim.tiles[lastNonBedrock][x] != TileIndex::Bedrock) { allBedrock = false; break; }
        }
        if (!allBedrock) break;
        --lastNonBedrock;
    }

    // prefer stored viewport height for a stable half-view calculation
    float halfViewH = (screenH > 0) ? (screenH * 0.5f) / camera.zoom : camera.offset.y / camera.zoom;
    float minViewTop = firstNonBedrock * tileHeight;
    float maxViewBottom = (lastNonBedrock + 1) * tileHeight;

    minTargetY = minViewTop + halfViewH;
    maxTargetY = maxViewBottom - halfViewH;

    if (minTargetY > maxTargetY) {
        float mid = (minTargetY + maxTargetY) * 0.5f;
        minTargetY = maxTargetY = mid;
    }

    // as a safety, ensure targets are finite
    if (!std::isfinite(minTargetY)) minTargetY = 0.0f;
    if (!std::isfinite(maxTargetY)) maxTargetY = 0.0f;
}

void CameraManager::UpdateFollow(const Player& player)
{
    Rectangle playerHitbox = player.hitbox;

    static bool updateX = false;

    float playerCenterX = playerHitbox.x + playerHitbox.width * 0.5f;
    float playerCenterY = playerHitbox.y + playerHitbox.height * 0.5f;

    float halfScreen = screenW * 0.5f;

    float triggerRatio = procentageFromScreenToTriggerCameraUpdateX / 100.0f;
    float stopRatio    = procentageFromScreenToStopCameraUpdateX / 100.0f;

    // OUTER trigger zone
    float leftBoundaryStart  = camera.target.x - halfScreen * (1.0f - triggerRatio);
    float rightBoundaryStart = camera.target.x + halfScreen * (1.0f - triggerRatio);

    // INNER stop zone
    float leftBoundaryStop  = camera.target.x - halfScreen * (1.0f - stopRatio);
    float rightBoundaryStop = camera.target.x + halfScreen * (1.0f - stopRatio);

    // Start following when leaving outer safe zone
    if (playerCenterX < leftBoundaryStart ||
        playerCenterX > rightBoundaryStart)
    {
        updateX = true;
    }

    // Stop following only after re-entering inner zone
    if (playerCenterX > leftBoundaryStop &&
        playerCenterX < rightBoundaryStop)
    {
        updateX = false;
    }

    Vector2 target = { playerCenterX, playerCenterY };

    // Lookahead
    target.x += player.speed * player.movementUnitVector.x * 2.f;
    target.y += player.speed * player.movementUnitVector.y * 0.25f;

    float smoothFactor = 0.008f;

    if (updateX)
    {
        camera.target.x +=
            (target.x - camera.target.x) * smoothFactor;
    }

    camera.target.y +=
        (target.y - camera.target.y) * smoothFactor;

    // Clamp Y
    float clampedY = playerCenterY;

    if (minTargetY <= maxTargetY)
    {
        clampedY =
            std::max(minTargetY,
            std::min(playerCenterY, maxTargetY));
    }

    camera.target.y = clampedY;
}