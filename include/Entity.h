#pragma once

#include "raylib.h"
#include "DimensionManager.h"
#include <utility>

class Entity {
public:
    int hp;
    int damagePerHit;
    float speed;
    Vector2 movementUnitVector;
    Rectangle hitbox;
    int id;
    
    virtual void Update(Dimension& currentDimension, float deltaTime);
    virtual void Draw() const;
    virtual void DrawDebug() const;
    
protected:
    bool CollisionCheck(const Entity& other) const;
    bool OnGroundCheck(const Dimension& currentDimension) const;
    void SnapToGround(const Dimension& currentDimension);
    void SnapToSideTile(const Dimension& currentDimension, float nextX, bool movingRight);
    bool IsSolidTile(const Dimension& currentDimension, int tileX, int tileY) const;
    bool RectangleHitsSolidTile(const Dimension& currentDimension, const Rectangle& rect) const;

    std::pair<int, int> ToIndex(Vector2 position) const;

    bool isJumping = false; 
};
