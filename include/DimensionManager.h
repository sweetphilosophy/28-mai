#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <queue>
#include "CameraManager.h"
#include "TextureManager.h"

struct Action {
    std::pair<int, int> position;
    int newTileID;
};

struct Dimension {
public:
    Dimension(std::string filename, bool isActive = false);
    ~Dimension() = default;

    // filename should include extension, e.g. ".png"
    // filename should be a path relative to the executable, e.g. "assets\\maps\\my_map.png"
    void LoadFromFile(std::string filename);
    void SaveToFile(std::string filename) const;
    float getWidth() const;
    float getHeight() const;
    int WrapX(int x) const;
    float WrapX(float x) const;

    void Update();
    // draws seemplesly looping map
    void Draw(const CameraManager& cameraManager, const TextureManager& textureManager, const bool debugDraw = true) const;
    
    const char* GetNameFromID(int tileID) const;

    std::queue<Action> updateQueue; // Queue for pending updates (e.g., tile changes)
    std::vector<std::vector<int>> tiles;

    // if inactive, the dimension will not be updated or drawn
    bool isActive;

private:
    bool inBounds(float x, float y) const;
    bool inBounds(std::pair<float, float> pos) const;
    void DrawIndividualMap(const CameraManager& cameraManager, const TextureManager& textureManager, float offsetX = 0.0f) const;
    // draws colored rectangles with togglable (TAB-key) tile ID display for testing
    void DrawIndividualMap_debug(const CameraManager& cameraManager, float offsetX = 0.0f) const;
};

struct DimensionManager {
public:
    DimensionManager() = default;
    ~DimensionManager() = default;

    void Update();
    void Draw(const CameraManager& cameraManager, const TextureManager& textureManager) const;

    const Dimension& GetCurrentDimension() const;
    Dimension& GetCurrentDimension();

    std::vector<Dimension> dimensions;

    int currentDimensionIndex = 0;
};