#include "CameraManager.h"
#include <algorithm>
#include <cmath>

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

void CameraManager::UpdateFollow(const Rectangle& playerHitbox, const Dimension& dim) {

    float playerCenterY = playerHitbox.y + playerHitbox.height * 0.5f;
    float playerCenterX = playerHitbox.x + playerHitbox.width * 0.5f;

    camera.target.x = playerCenterX;

    // Clamp Y to configured vertical limits. If limits are equal we still clamp to that value.
    float clampedY = playerCenterY;
    if (minTargetY <= maxTargetY) clampedY = std::max(minTargetY, std::min(playerCenterY, maxTargetY));
    camera.target.y = clampedY;
}