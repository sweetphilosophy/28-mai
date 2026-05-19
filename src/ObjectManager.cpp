#include "ObjectManager.h"
#include "Config.h"
#include "Bee.h"

ObjectManager::ObjectManager() {
    // Initialize properties if needed

    player.hp = 100;
    player.damagePerHit = 10;
    player.speed = 200.0f; // Example speed value
    player.hitbox = {100, 270, 32, 64}; // Example starting position and size
    player.entityID = EntityID::PLAYER;

    // Temporary: Add a bee entity for testing
    // Add a bee entity
    enemies.push_back(std::make_unique<Bee>(Vector2{60, tileHeight * (67 - 32)}, DimensionID::Overworld));
}

void ObjectManager::Input(DimensionManager& dimManager, CameraManager& cameraManager) {
    player.Input(dimManager, cameraManager);
}

void ObjectManager::Update(DimensionManager& dimManager, CameraManager& cameraManager, float dt) {
    player.Update(dimManager.GetCurrentDimension(), dt);
    
    // Update all enemies
    for (auto& enemy : enemies) {
        enemy->Update(dimManager.GetCurrentDimension(), dt, &player);
    }
    
    cameraManager.UpdateFollow(player, dimManager.GetCurrentDimension());
}

void ObjectManager::Draw(DimensionManager& dimManager) const {
    // Draw player
    player.Draw(dimManager);
      
    static bool debugDraw = false; // Toggle for debug drawing
    
    // toggle between draw debug and normal draw
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_O)) {
        debugDraw = !debugDraw;
        TraceLog(LOG_INFO, "Toggled debug draw: %s", debugDraw ? "ON" : "OFF");
    }

    if (debugDraw) {
        player.DrawDebug(dimManager);

        for (const auto& enemy : enemies) {
            enemy->DrawDebug(dimManager);
        }

        return;
    }


    // Draw all enemies
    for (const auto& enemy : enemies) {
        enemy->Draw();
    }
}