#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    void HandleMovement();
    void HandleMouse();
};
