#include "UI_Manager.h"
#include "Config.h"

void UI_Manager::draw(ObjectManager& objectManager, InventoryManager& InventoryManager, DimensionManager& dimensionManager) {
    objectManager.player.DrawHandling_CreativeModeUI(dimensionManager);
    InventoryManager.Draw();

    DrawHPbar(objectManager);

    // draw debug coordinates
    DrawText(TextFormat("Player Position: (%.0f, %.0f)", objectManager.player.hitbox.x / tileWidth, objectManager.player.hitbox.y / tileHeight), SCREEN_WIDTH - 800, 40, 16, BLACK);
}

void UI_Manager::DrawHPbar(const ObjectManager& objectManager) const {

    DrawRectangle(HPbarX, HPbarY, HPbarWidth, HPbarHeight, RED); // background
    float healthRatio = (float)objectManager.player.currentHealth / objectManager.player.maxHealth;
    DrawRectangle(HPbarX, HPbarY, (int)(HPbarWidth * healthRatio), HPbarHeight, GREEN); // fill
    DrawRectangleLines(HPbarX, HPbarY, HPbarWidth, HPbarHeight, BLACK); // border
    DrawText(TextFormat("HP: %d/%d", objectManager.player.currentHealth, objectManager.player.maxHealth), HPbarX, HPbarY + HPbarHeight + 5, 16, BLACK);
}