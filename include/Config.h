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
