#include "Player.h"
#include "raylib.h"

void Player::HandleMovement() {
    movementUnitVector = {0, 0};
    if (IsKeyDown(KEY_W)) {
        movementUnitVector.y = -1;
    }
    if (IsKeyDown(KEY_S)) {
        movementUnitVector.y = 1;
    }
    if (IsKeyDown(KEY_A)) {
        movementUnitVector.x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        movementUnitVector.x = 1;
    }

    hitbox.x += movementUnitVector.x * speed;
    hitbox.y += movementUnitVector.y * speed;
}

void Player::HandleMouse() {
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    }
}
