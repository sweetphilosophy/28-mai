#pragma once

#include <vector>
#include <string>
#include <cstdint>

struct Dimension {
    Dimension(std::string filename);
    ~Dimension() = default;
    void LoadFromFile(std::string filename);
    void SaveToFile(std::string filename) const;
    int getWidth() const;
    int getHeight() const;

    std::vector<std::vector<uint8_t>> tiles;
};

struct HandleDimensions {
public:
    HandleDimensions() = default;
    ~HandleDimensions() = default;

    void Update();
    void Draw() const;

    // draws the initial png colors only
    void Draw_MapDebug() const;

    std::vector<Dimension> dimensions;

    int currentDimensionIndex = 0;
};