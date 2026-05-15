#include "InventoryManager.h"
#include "Config.h"

InventoryManager::InventoryManager() {
    selectedSlot = -1;
    isOpen = false;
    inventoryItems.resize(inventorySlotCount, {0, 0}); // Initialize all slots with item ID 0 and quantity 0
}

void InventoryManager::Draw() const {
    if (!isOpen) {
        
        for (int i = 0; i < 9; i++) {
            int slotX = inventoryNotOpenStartX + i * (inventorySlotSize + inventorySlotSpacing);
            int slotY = inventoryNotOpenStartY;
            
            DrawRectangle(slotX, slotY, inventorySlotSize, inventorySlotSize, LIGHTGRAY);
            DrawRectangleLines(slotX, slotY, inventorySlotSize, inventorySlotSize, BLACK);

            if (i == selectedSlot) {
                Rectangle outline = {(float)slotX, (float)slotY, (float)inventorySlotSize, (float)inventorySlotSize};
                DrawRectangleLinesEx(outline, 3, YELLOW);
            }
            
            DrawText(TextFormat("%d", i + 1), slotX + 5, slotY + 5, 16, BLACK);
        }

        DrawText("Press I to open InventoryManager", 10, 60, 16, DARKGRAY);
        return;
    }

    Rectangle panel = {(float)inventoryOpenStartX - 20.f, (float)inventoryOpenStartY - 50.f, (float)inventoryOpenTotalWidth + 40.f, (float)inventoryOpenTotalHeight + 80.f};
    DrawRectangleRec(panel, Fade(DARKGRAY, 0.8f));
    DrawRectangleLinesEx(panel, 2.f, BLACK);

    DrawText("InventoryManager (press I to close)", inventoryOpenStartX, inventoryOpenStartY - 40, 20, RAYWHITE);

    for (int row = 0; row < inventoryRows; row++) {
        for (int col = 0; col < inventoryCollums; col++) {
            int i = row * inventoryCollums + col;
            int slotX = inventoryOpenStartX + col * (inventorySlotSize + inventorySlotSpacing);
            int slotY = inventoryOpenStartY + row * (inventorySlotSize + inventorySlotSpacing);

            DrawRectangle(slotX, slotY, inventorySlotSize, inventorySlotSize, LIGHTGRAY);
            DrawRectangleLines(slotX, slotY, inventorySlotSize, inventorySlotSize, BLACK);

            if (i == selectedSlot) {
                Rectangle outline = {(float)slotX, (float)slotY, (float)inventorySlotSize, (float)inventorySlotSize};
                DrawRectangleLinesEx(outline, 3, YELLOW);
            }

            if (i < 8) { // Only label the first 8 slots with numbers
                DrawText(TextFormat("%d", i + 1), slotX + 6, slotY + 6, 16, BLACK);
            }
        }
    }
}

void InventoryManager::Input() {
    if (IsKeyPressed(KEY_I)) {
        isOpen = !isOpen;
        return;
    }

    // Handle InventoryManager slot hotkey selection
    for (int i = KEY_ONE; i <= KEY_EIGHT; i++) {
        if (IsKeyPressed(i)) {
            selectedSlot = i - KEY_ONE;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        int slotSize = 40;
        int slotSpacing = isOpen ? 6 : 5;
        int startX = isOpen ? (GetScreenWidth() - (8 * slotSize + 7 * slotSpacing)) / 2 : 10;
        int startY = isOpen ? (GetScreenHeight() - (5 * slotSize + 4 * slotSpacing)) / 2 : 10;
        int cols = isOpen ? 8 : 9;
        int rows = isOpen ? 5 : 1;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int i = row * cols + col;
                int slotX = startX + col * (slotSize + slotSpacing);
                int slotY = startY + row * (slotSize + slotSpacing);
                Rectangle slotBounds = {(float)slotX, (float)slotY, (float)slotSize, (float)slotSize};

                if (CheckCollisionPointRec(mousePos, slotBounds)) {
                    selectedSlot = i;
                    return;
                }
            }
        }
    }
}
