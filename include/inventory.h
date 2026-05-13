#pragma once

#include "raylib.h"
#include "Config.h"

class Inventory {
public:
    Inventory();
    void Draw() const;
    void HandleInput();

private:
    int selectedSlot;
    bool isOpen;
};