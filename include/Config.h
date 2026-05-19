#pragma once
#include "raylib.h"

constexpr float tileWidth = 32;
constexpr float tileHeight = 32;

constexpr int targetFPS = 60;

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

constexpr float gravity = 1800.0f;
constexpr float jumpVelocity = -600.0f; // Initial jump velocity (negative for upward movement)

constexpr int updatesPerFrame = 5; // Number of tile updates to process per frame

// used as parameter for dimension loading to remove arbitray "magic" numbers in the code
constexpr bool SetToActiveDimension = true;
// used as parameter for dimension loading to remove arbitray "magic" numbers in the code
constexpr bool SetToInactiveDimension = false;

// used as parameter for dimension drawing to remove arbitray "magic" numbers in the code
constexpr bool SetToTextureDraw = false;

// InventoryManager propeties
constexpr int   inventoryCollums = 8;
constexpr int   inventoryRows = 5;
constexpr int   inventorySlotCount = inventoryCollums * inventoryRows;
constexpr float inventorySlotSize = 40;
constexpr float inventorySlotSpacing = 6;

constexpr float inventoryNotOpenStartX = 10;
constexpr float inventoryNotOpenStartY = 10;

constexpr float inventoryOpenTotalWidth = inventoryCollums * inventorySlotSize + (inventoryCollums - 1) * inventorySlotSpacing;
constexpr float inventoryOpenTotalHeight = inventoryRows * inventorySlotSize + (inventoryRows - 1) * inventorySlotSpacing;
constexpr float inventoryOpenStartX = (SCREEN_WIDTH - inventoryOpenTotalWidth) / 2;
constexpr float inventoryOpenStartY = (SCREEN_HEIGHT - inventoryOpenTotalHeight) / 2;


// hp bar properties
constexpr float HPbarWidth = 200;
constexpr float HPbarHeight = 15;
constexpr float HPbarX = SCREEN_WIDTH - HPbarWidth - 20;
constexpr float HPbarY = 20;

// Entity properties
constexpr float playerSpeed = 200.0f; // Example speed value for the player
constexpr int   playerHP = 100;

constexpr float beeChasingSpeed = 80.0f;
constexpr float beeWanderingSpeed = 40.0f;
constexpr float beeChasingDetectionRange = tileWidth * 10.0f;
constexpr float beeWanderingBoundingBoxX = tileWidth * 10.0f; // Size of the bounding box for wandering behavior
constexpr float beeWanderingBoundingBoxY = tileHeight * 10.0f; // Size of the bounding box for wandering behavior
constexpr float beeBobbleAmplitude = tileHeight * 0.25f;
constexpr float beeBobbleFrequency = 2.0f;
constexpr int   beeHP = 20;
constexpr int   beeDamagePerHit = 5;

// hitbox sizes
constexpr Vector2 playerHitboxSize = {tileWidth, tileHeight * 2}; // Player is 2 tiles tall
constexpr Vector2 beeHitboxSize = {tileWidth, tileHeight};

namespace EntityID {
    enum : int {
        PLAYER,
        BEE,
        EntityCount,
        NONE = -1
    };
}

namespace TileIndex {
    enum : int {
        Air,
        Dirt,
        Grass,
        Wood,
        LeafBlock,
        Stone,
        Planks,
        Bedrock,
        BlueObsidian,
        TileCount
    };
}

namespace DimensionID {
    enum : int {
        Overworld,
        // BlueNether,
        // RedNether,
        // SlimeDimension,
        DimensionCount
    };
}

constexpr const char* saveDirectory = "assets\\misc";

constexpr const char* staticTextureDirectory = "assets\\sprites\\static";
constexpr const char* staticTexturesFilenames[TileIndex::TileCount] = {
    "no_texture.png", // Placeholder for index 0 (Air)
    "dirt.png",
    "grass.png",
    "wood.png",
    "leaf_block.png",
    "stone.png",
    "planks.png",
    "bedrock.png",
    "blue_obsidian.png"
};
