#include "Entity.h"
#include "raylib.h"
#include "Config.h"
#include <cmath>

std::pair<int, int> Entity::ToIndex(Vector2 position) const {
    int tileX = position.x / tileWidth;
    int tileY = position.y / tileHeight;
    return {tileX, tileY};
}

bool Entity::CollisionCheck(const Entity& other) const {
    return CheckCollisionRecs(this->hitbox, other.hitbox);
}

bool Entity::IsSolidTile(const Dimension& currentDimension, int tileX, int tileY) const {
    if (tileY < 0 || tileY >= (int)currentDimension.tiles.size()) {
        return false;
    }

    if (tileX < 0 || tileX >= (int)currentDimension.tiles[tileY].size()) {
        return false;
    }

    return currentDimension.tiles[tileY][tileX] != TileIndex::Air;
}

bool Entity::RectangleHitsSolidTile(const Dimension& currentDimension, const Rectangle& rect) const {
    if (currentDimension.tiles.empty()) {
        return false;
    }

    int left = (int)std::floor(rect.x / tileWidth);
    int right = (int)std::floor((rect.x + rect.width - 1.0f) / tileWidth);
    int top = (int)std::floor(rect.y / tileHeight);
    int bottom = (int)std::floor((rect.y + rect.height - 1.0f) / tileHeight);

    for (int y = top; y <= bottom; ++y) {
        for (int x = left; x <= right; ++x) {
            if (IsSolidTile(currentDimension, x, y)) {
                return true;
            }
        }
    }

    return false;
}

bool Entity::OnGroundCheck(const Dimension& currentDimension) const {
    Rectangle probe = hitbox;
    probe.y += 1.0f; // useful threshold to prevent floating point precision issues
    return RectangleHitsSolidTile(currentDimension, probe);
}

void Entity::SnapToGround(const Dimension& currentDimension) {
    int left = (int)std::floor(hitbox.x / tileWidth);
    int right = (int)std::floor((hitbox.x + hitbox.width - 1.0f) / tileWidth);
    int bottom = (int)std::floor((hitbox.y + hitbox.height - 1.0f) / tileHeight);

    for (int y = bottom; y >= 0; --y) {
        for (int x = left; x <= right; ++x) {
            if (IsSolidTile(currentDimension, x, y)) {
                hitbox.y = y * tileHeight - hitbox.height;
                return;
            }
        }
    }

    // add error state handling if no solid tile is found
    // do it with logging or throw an exception
}

void Entity::SnapToSideTile(const Dimension& currentDimension, float nextX, bool movingRight) {
    int top = (int)std::floor(hitbox.y / tileHeight);
    int bottom = (int)std::floor((hitbox.y + hitbox.height - 1.0f) / tileHeight);
    int sideX = movingRight ? (int)std::floor((nextX + hitbox.width - 1.0f) / tileWidth) : (int)std::floor(nextX / tileWidth);

    for (int y = top; y <= bottom; ++y) {
        if (IsSolidTile(currentDimension, sideX, y)) {
            if (movingRight) {
                hitbox.x = sideX * tileWidth - hitbox.width;
            } else {
                hitbox.x = (sideX + 1) * tileWidth;
            }
            return;
        }
    }

    // add error state handling if no solid tile is found
    // do it with logging or throw an exception
}

void Entity::Update(Dimension& currentDimension, float deltaTime) {
    // Base entity update logic (if any) can go here
}

void Entity::Draw() const {
    // draw texture based on id, use texture manager to get current frame of animation if the case
}

void Entity::DrawDebug() const {
    DrawRectangleLinesEx(hitbox, 2, RED);
}
