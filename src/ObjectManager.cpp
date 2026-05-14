#include "ObjectManager.h"
#include "Config.h"

ObjectManager::ObjectManager() {
    // Initialize properties if needed

    player.hp = 100;
    player.damagePerHit = 10;
    player.speed = 200.0f; // Example speed value
    player.hitbox = {100, 270, 32, 64}; // Example starting position and size
    player.id = EntityID::PLAYER;

    // Add a bee entity
    entities.push_back(std::make_unique<Bee>(Vector2{200, 200}, 0));
}

void ObjectManager::Input(DimensionManager& dimManager, CameraManager& cameraManager) {
    player.Input(dimManager, cameraManager);
}

void ObjectManager::Update(DimensionManager& dimManager, CameraManager& cameraManager, float dt) {
    player.Update(dimManager.GetCurrentDimension(), dt);
    
    // Update all entities
    for (auto& entity : entities) {
        entity->Update(dimManager.GetCurrentDimension(), dt);
    }
    
    cameraManager.UpdateFollow(player.hitbox, dimManager.GetCurrentDimension());
}

void ObjectManager::Draw(DimensionManager& dimManager) const {
    // Draw player debug rectangle
    player.DrawDebug(dimManager);

    // Draw all entities
    for (const auto& entity : entities) {
        entity->Draw();
    }
}

void ObjectManager::DrawDebug(const DimensionManager& dimManager) const {
    player.DrawDebug(dimManager);
    
    // Draw debug for all entities
    for (const auto& entity : entities) {
        entity->DrawDebug(dimManager);
    }
}