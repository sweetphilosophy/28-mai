#pragma once

#include "raylib.h"
#include <vector>

class InventoryManager {
public:
    InventoryManager();
    void Input();
    void Draw() const;

private:
    int selectedSlot;
    bool isOpen;
    // holds item IDs and quantities for each inventory slot
    std::vector<std::pair<int, int>> inventoryItems;
};