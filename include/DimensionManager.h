#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <queue>
#include "CameraManager.h"

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
    int getWidth() const;
    int getHeight() const;
    int WrapX(int x) const;

    void Update();
    // draws seemplesly looping map
    void Draw() const;
    // draws in a seemless loop, the initial png colors only
    void Draw_MapDebug(const CameraManager& cameraManager) const;
    
    const char* GetNameFromID(int tileID) const;

    std::queue<Action> updateQueue; // Queue for pending updates (e.g., tile changes)
    std::vector<std::vector<int>> tiles;

    // if inactive, the dimension will not be updated or drawn
    bool isActive;

private:
    bool inBounds(int x, int y) const;
    bool inBounds(std::pair<int, int> pos) const;
    void DrawIndividualMap(const CameraManager& cameraManager, float offsetX = 0.0f) const;
};

struct DimensionManager {
public:
    DimensionManager() = default;
    ~DimensionManager() = default;

    void Update();
    void Draw() const;
    // draws the initial png colors only
    void Draw_MapDebug(const CameraManager& cameraManager) const;

    const Dimension& GetCurrentDimension() const;
    Dimension& GetCurrentDimension();

    std::vector<Dimension> dimensions;

    int currentDimensionIndex = 0;
};