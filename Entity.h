#pragma once

#include "raylib.h"

enum EntityType {
    PLAYER,
    BEE
};

class Entity {
public:
    int hp;
    int dmg;
    float speed;
    Vector2 movementUnitVector;
    Rectangle hitbox;
    int id;

    bool CollisionCheck(const Entity& other) const;
    bool OnGroundCheck() const;
    void Update();
    void DrawDebug() const;
};
