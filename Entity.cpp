#include "Entity.h"
#include "raylib.h"

bool Entity::CollisionCheck(const Entity& other) const {
    return CheckCollisionRecs(this->hitbox, other.hitbox);
}

bool Entity::OnGroundCheck() const {
    return false;
}

void Entity::Update() {
}

void Entity::DrawDebug() const {
    DrawRectangleLinesEx(hitbox, 2, RED);
}
