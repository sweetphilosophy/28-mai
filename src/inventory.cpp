#include "inventory.h"

Inventory::Inventory()
    : selectedSlot(-1)
    , isOpen(false) {
}

void Inventory::Draw() const {
    if (!isOpen) {
        int slotSize = 40;
        int slotSpacing = 5;
        int startX = 10;
        int startY = 10;
        
        for (int i = 0; i < 9; i++) {
            int slotX = startX + i * (slotSize + slotSpacing);
            int slotY = startY;
            
            DrawRectangle(slotX, slotY, slotSize, slotSize, LIGHTGRAY);
            DrawRectangleLines(slotX, slotY, slotSize, slotSize, BLACK);

            if (i == selectedSlot) {
                Rectangle outline = {(float)slotX, (float)slotY, (float)slotSize, (float)slotSize};
                DrawRectangleLinesEx(outline, 3, YELLOW);
            }
            
            DrawText(TextFormat("%d", i + 1), slotX + 5, slotY + 5, 16, BLACK);
        }

        DrawText("Press I to open inventory", 10, 60, 16, DARKGRAY);
        return;
    }

    int cols = 8;
    int rows = 5;
    int slotSize = 40;
    int slotSpacing = 6;
    int totalWidth = cols * slotSize + (cols - 1) * slotSpacing;
    int totalHeight = rows * slotSize + (rows - 1) * slotSpacing;
    int startX = (GetScreenWidth() - totalWidth) / 2;
    int startY = (GetScreenHeight() - totalHeight) / 2;

    Rectangle panel = {(float)startX - 20.f, (float)startY - 50.f, (float)totalWidth + 40.f, (float)totalHeight + 80.f};
    DrawRectangleRec(panel, Fade(DARKGRAY, 0.8f));
    DrawRectangleLinesEx(panel, 2.f, BLACK);

    DrawText("Inventory (press I to close)", startX, startY - 40, 20, RAYWHITE);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int i = row * cols + col;
            int slotX = startX + col * (slotSize + slotSpacing);
            int slotY = startY + row * (slotSize + slotSpacing);

            DrawRectangle(slotX, slotY, slotSize, slotSize, LIGHTGRAY);
            DrawRectangleLines(slotX, slotY, slotSize, slotSize, BLACK);

            if (i == selectedSlot) {
                Rectangle outline = {(float)slotX, (float)slotY, (float)slotSize, (float)slotSize};
                DrawRectangleLinesEx(outline, 3, YELLOW);
            }

            if (i < 9) {
                DrawText(TextFormat("%d", i + 1), slotX + 6, slotY + 6, 16, BLACK);
            }
        }
    }
}

void Inventory::HandleInput() {
    if (IsKeyPressed(KEY_I)) {
        isOpen = !isOpen;
        return;
    }

    // Handle number key input (1-9)
    if (IsKeyPressed(KEY_ONE)) {
        selectedSlot = 0;
    }
    if (IsKeyPressed(KEY_TWO)) {
        selectedSlot = 1;
    }
    if (IsKeyPressed(KEY_THREE)) {
        selectedSlot = 2;
    }
    if (IsKeyPressed(KEY_FOUR)) {
        selectedSlot = 3;
    }
    if (IsKeyPressed(KEY_FIVE)) {
        selectedSlot = 4;
    }
    if (IsKeyPressed(KEY_SIX)) {
        selectedSlot = 5;
    }
    if (IsKeyPressed(KEY_SEVEN)) {
        selectedSlot = 6;
    }
    if (IsKeyPressed(KEY_EIGHT)) {
        selectedSlot = 7;
    }
    if (IsKeyPressed(KEY_NINE)) {
        selectedSlot = 8;
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
