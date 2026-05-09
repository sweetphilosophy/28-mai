#include "ObjectManager.h"
#include "Config.h"

ObjectManager::ObjectManager() {
    // Initialize properties if needed

    player.hp = 100;
    player.damagePerHit = 10;
    player.speed = 200.0f; // Example speed value
    player.hitbox = {100, 270, 32, 64}; // Example starting position and size
    player.id = EntityID::PLAYER;
}

void ObjectManager::Input(DimensionManager& dimManager, CameraManager& cameraManager) {
    player.Input(dimManager, cameraManager);
}

void ObjectManager::Update(DimensionManager& dimManager, CameraManager& cameraManager, float dt) {
    player.Update(dimManager.GetCurrentDimension(), dt);
    cameraManager.UpdateFollow(player.hitbox, dimManager.GetCurrentDimension());
}

void ObjectManager::Draw(DimensionManager& dimManager) const {
    player.DrawDebug(dimManager);
}

void ObjectManager::DrawDebug(const DimensionManager& dimManager) const {
    player.DrawDebug(dimManager);
}