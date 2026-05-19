#include "ObjectManager.h"
#include "Config.h"
#include "Bee.h"
#include "Entity.h"

ObjectManager::ObjectManager() {
    // Initialize properties if needed

    player.hp = 100;
    player.damagePerHit = 10;
    player.speed = 200.0f; // Example speed value
    player.hitbox = {100, 270, 32, 64}; // Example starting position and size
    player.entityID = EntityID::PLAYER;

    // Temporary: Add a bee entity for testing
    // Add a bee entity
    // enemies.push_back(std::make_unique<Bee>(Vector2{60, tileHeight * (67 - 32)}, DimensionID::Overworld));
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
    
    if (ShouldUpdateRandomEntityAction(dt)) {
        HandlePlayerEntityInteractions(dimManager.GetCurrentDimension());
        HandleEntitySpawning(dimManager.GetCurrentDimension());
        HandleEntityDespawning(dimManager.GetCurrentDimension(), cameraManager);
    }

    cameraManager.UpdateFollow(player);
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

void ObjectManager::HandlePlayerEntityInteractions(Dimension& currentDimension) {
    // Placeholder for player-entity interaction logic (e.g., combat, item pickup)
}

void ObjectManager::HandleEntitySpawning(Dimension& currentDimension) {
    
    SetRandomSeed(GetTime()); // Ensure randomness for spawning behavior
    
    // Spawn entities with a small chance per update, up to a maximum
    if ((int)enemies.size() >= maxSpawnedEntities) return;

    // Roll a percentage chance to spawn
    int roll = GetRandomValue(1, 100);
    if (roll > entitySpawnChancePerUpdate) return;

    // Determine spawn X so it appears outside the player's current viewport.
    // We don't have CameraManager here, so approximate "outside view" as at least one screen width away from player.
    float playerCenterX = player.hitbox.x + player.hitbox.width / 2.0f;

    float spawnDistance = (float)SCREEN_WIDTH; // pixels
    bool spawnLeft = GetRandomValue(0, 1) == 0;

    float spawnX = spawnLeft ? playerCenterX - spawnDistance : playerCenterX + spawnDistance;

    // set random offset for spawnX
    spawnX += GetRandomValue(0, (int)spawnDistance / 2) - (spawnDistance / 4); // random offset within +/- spawnDistance/4

    int heightOffset = GetRandomValue(1, 5);
    int lookupTileX = (int)(spawnX / tileWidth);
    int topBlockY = Entity::GetAvailableTopBlockAtX(currentDimension, lookupTileX);
    // Debug: log the tile lookup values
    TraceLog(LOG_INFO, "Spawning lookup tileX=%i topBlockY=%i (mapHeight=%i)", lookupTileX, topBlockY, (int)currentDimension.getHeight());
    // Convert tile index to pixel Y. Subtract bee height and additional tile offsets in pixels.
    float spawnY = topBlockY * tileHeight - beeHitboxSize.y - heightOffset * tileHeight;

    Vector2 spawnPos = { spawnX, spawnY };

    // Create a Bee for now; could choose other enemy types in future
    enemies.push_back(std::make_unique<Bee>(spawnPos, DimensionID::Overworld));
    TraceLog(LOG_INFO, "Spawned new enemy at (%.2f, %.2f). Total enemies: %i", spawnX / tileWidth, spawnY / tileHeight, (int)enemies.size());
}

void ObjectManager::HandleEntityDespawning(Dimension& currentDimension, const CameraManager& cameraManager) {
    SetRandomSeed(GetTime()); // Ensure randomness for despawning behavior

    // Placeholder for entity despawning logic (e.g., removing enemies that are too far away)

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        // Roll a percentage chance to despawn
        int roll = GetRandomValue(1, 100);
        if (roll > entityDespawnChancePerUpdate) {
            ++it;
            continue;
        }

        // if is on camera, don't despawn
        if ((*it)->inScreenBounds(cameraManager)) {
            ++it;
            continue;
        }

        TraceLog(LOG_INFO, "Despawning enemy at (%.2f, %.2f). Total enemies after despawn: %i", (*it)->hitbox.x / tileWidth, (*it)->hitbox.y / tileHeight, (int)enemies.size() - 1);
        it = enemies.erase(it);
    }
}

bool ObjectManager::ShouldUpdateRandomEntityAction(float dt) {
    static float timeSinceLastUpdate = 0.0f;
    timeSinceLastUpdate += dt;
    
    if (timeSinceLastUpdate >= randomActionUpdateFrequency) {
        timeSinceLastUpdate = 0.0f;
        return true;
    }
    
    return false;
}