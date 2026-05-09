#pragma once

constexpr int tileWidth = 32;
constexpr int tileHeight = 32;

constexpr int targetFPS = 60;

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

constexpr float gravity = 1800.0f;
constexpr float jumpVelocity = -600.0f; // Initial jump velocity (negative for upward movement)

constexpr int updatesPerFrame = 5; // Number of tile updates to process per frame

constexpr bool isActiveDimension = true;
constexpr bool isInactiveDimension = false;

constexpr const char* saveDirectory = "assets\\misc";

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