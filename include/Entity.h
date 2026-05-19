#pragma once

#include "raylib.h"
#include "DimensionManager.h"
#include <utility>

struct Dimension; // Forward declaration to avoid circular dependency
struct DimensionManager; // Forward declaration to avoid circular dependency

class Entity {
public:
    int hp;
    int damagePerHit;
    float speed;
    Vector2 movementUnitVector;
    Rectangle hitbox;
    int entityID; // Entity type identifier, e.g., player, bee, etc.
    int dimensionID; // Dimension ID where the entity is located
    
    virtual void Update(Dimension& currentDimension, float deltaTime);
    virtual void Draw() const;
    virtual void DrawDebug(const DimensionManager& dimManager) const;
    Vector2 GetCenter() const {
        return { hitbox.x + hitbox.width / 2, hitbox.y + hitbox.height / 2 };
    }
    static int GetAvailableTopBlockAtX(const Dimension& currentDimension, int x);

    static bool IsSolidTile(const Dimension& currentDimension, int tileX, int tileY);
    bool inScreenBounds(const CameraManager& cameraManager) const;

protected:
    bool CollisionCheck(const Entity& other) const;
    bool OnGroundCheck(const Dimension& currentDimension) const;
    void SnapToGround(const Dimension& currentDimension);
    void SnapToSideTile(const Dimension& currentDimension, float nextX, bool movingRight);
    bool RectangleHitsSolidTile(const Dimension& currentDimension, const Rectangle& rect) const;
    std::pair<int, int> ToIndex(Vector2 position) const;

    bool isJumping = false; 
};
