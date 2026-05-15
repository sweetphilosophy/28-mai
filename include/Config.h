#pragma once

constexpr int tileWidth = 32;
constexpr int tileHeight = 32;

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
constexpr int inventoryCollums = 8;
constexpr int inventoryRows = 5;
constexpr int inventorySlotCount = inventoryCollums * inventoryRows;
constexpr int inventorySlotSize = 40;
constexpr int inventorySlotSpacing = 6;

constexpr int inventoryNotOpenStartX = 10;
constexpr int inventoryNotOpenStartY = 10;

constexpr int inventoryOpenTotalWidth = inventoryCollums * inventorySlotSize + (inventoryCollums - 1) * inventorySlotSpacing;
constexpr int inventoryOpenTotalHeight = inventoryRows * inventorySlotSize + (inventoryRows - 1) * inventorySlotSpacing;
constexpr int inventoryOpenStartX = (SCREEN_WIDTH - inventoryOpenTotalWidth) / 2;
constexpr int inventoryOpenStartY = (SCREEN_HEIGHT - inventoryOpenTotalHeight) / 2;


// hp bar properties
constexpr int HPbarWidth = 200;
constexpr int HPbarHeight = 15;
constexpr int HPbarX = SCREEN_WIDTH - HPbarWidth - 20;
constexpr int HPbarY = 20;

namespace EntityID {
    enum : int {
        PLAYER,
        BEE
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
