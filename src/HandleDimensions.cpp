#include "include/HandleDimensions.h"
#include <unordered_map>
#include "raylib.h"

enum class TileIndex {
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

// fill in with preffered colors
// color code, index
static const std::unordered_map<uint32_t, uint8_t> colorCodeToIndex = {
    {0xFFFFFF, static_cast<uint8_t>(TileIndex::Air)},
    {0x964B00, static_cast<uint8_t>(TileIndex::Dirt)},
    {0x00FF00, static_cast<uint8_t>(TileIndex::Grass)},
    {0x8B4513, static_cast<uint8_t>(TileIndex::Wood)},
    {0x228B22, static_cast<uint8_t>(TileIndex::LeafBlock)},
    {0x808080, static_cast<uint8_t>(TileIndex::Stone)},
    {0xF5DEB3, static_cast<uint8_t>(TileIndex::Planks)},
    {0x4B4B4B, static_cast<uint8_t>(TileIndex::Bedrock)},
    {0x1E90FF, static_cast<uint8_t>(TileIndex::BlueObsidian)}
};

Color GetColorFromIndex(uint8_t index) {
    switch (static_cast<TileIndex>(index)) {
        case TileIndex::Air:          return GetColor(0xFFFFFFFF); // White for air (transparent)
        case TileIndex::Dirt:         return GetColor(0x964B00FF); // Raylib GetColor handles 0xRRGGBBAA
        case TileIndex::Grass:        return GetColor(0x00FF00FF);
        case TileIndex::Wood:         return GetColor(0x8B4513FF);
        case TileIndex::LeafBlock:    return GetColor(0x228B22FF);
        case TileIndex::Stone:        return GetColor(0x808080FF);
        case TileIndex::Planks:       return GetColor(0xF5DEB3FF);
        case TileIndex::Bedrock:      return GetColor(0x4B4B4BFF);
        case TileIndex::BlueObsidian: return GetColor(0x1E90FFFF);
        default:                      return WHITE; // Or any "error" color
    }
}

void Dimension::LoadFromFile(std::string filename) {
    // 1. Load the image into CPU memory
    Image mapImage = LoadImage(filename.c_str());
    
    if (mapImage.data == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load map image: %s", filename.c_str());
        return;
    }

    // 2. Initialise 2D vector size
    // tiles[y][x] structure
    tiles.assign(mapImage.height, std::vector<uint8_t>(mapImage.width, static_cast<uint8_t>(TileIndex::Air)));

    // 3. Iterate through every pixel
    for (int y = 0; y < mapImage.height; y++) {
        for (int x = 0; x < mapImage.width; x++) {
            
            // Get pixel color (returns Raylib Color struct: r, g, b, a)
            Color pix = GetImageColor(mapImage, x, y);

            // Convert RGB to a single uint32_t hex (ignore alpha for the map)
            uint32_t hexColor = (pix.r << 16) | (pix.g << 8) | pix.b;

            // 4. Look up the color in your map
            auto it = colorCodeToIndex.find(hexColor);
            if (it != colorCodeToIndex.end()) {
                tiles[y][x] = it->second;
            } else {
                // Default value if color isn't recognized
                tiles[y][x] = static_cast<uint8_t>(TileIndex::Air);
            }
        }
    }

    // 5. Unload image from CPU memory (very important!)
    UnloadImage(mapImage);
    
    TraceLog(LOG_INFO, "Dimension loaded: %i x %i tiles", mapImage.width, mapImage.height);
}

void Dimension::SaveToFile(std::string filename) const {
    // 1. Check if the vector is empty to avoid crashes
    if (tiles.empty() || tiles[0].empty()) {
        TraceLog(LOG_WARNING, "Cannot save dimension: tiles vector is empty.");
        return;
    }

    int height = (int)tiles.size();
    int width = (int)tiles[0].size();

    // 2. Generate a blank image in CPU memory
    // Format: PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    Image mapImage = GenImageColor(width, height, BLANK);

    // 3. Loop through the 2D vector and set pixel colors
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            // Get the tile ID
            uint8_t tileID = tiles[y][x];

            // Get the corresponding color
            Color tileColor = GetColorFromIndex(tileID);

            // Draw the pixel onto our image data
            ImageDrawPixel(&mapImage, x, y, tileColor);
        }
    }

    // 4. Export the image to a file
    // Raylib supports .png, .bmp, .tga, .jpg automatically based on extension
    if (ExportImage(mapImage, filename.c_str())) {
        TraceLog(LOG_INFO, "Dimension successfully saved to: %s", filename.c_str());
    } else {
        TraceLog(LOG_ERROR, "Failed to export dimension image: %s", filename.c_str());
    }

    // 5. Clean up the temporary image data
    UnloadImage(mapImage);
}

int Dimension::getWidth() const {
    return (tiles.empty()) ? 0 : (int)tiles[0].size();
}

int Dimension::getHeight() const {
    return (int)tiles.size();
}

Dimension::Dimension(std::string filename) {
    LoadFromFile(filename);
}

void HandleDimensions::Update() {
    // Placeholder for any future updates (e.g., animations, dynamic changes)
}

void HandleDimensions::Draw() const {
    // Placeholder for any future updates
}

void HandleDimensions::Draw_MapDebug() const {

    if (dimensions.empty()) {
        TraceLog(LOG_WARNING, "No dimensions to draw.");
        return;
    }

    if (currentDimensionIndex < 0 || currentDimensionIndex >= (int)dimensions.size()) {
        TraceLog(LOG_ERROR, "Current dimension index out of bounds: %i", currentDimensionIndex);
        return;
    }

    for (int i = 0; i < (int)dimensions.size(); i++) {
        const Dimension& dim = dimensions[i];
        int tileSize = 32; // Size of each tile in pixels

        for (int y = 0; y < dim.getHeight(); y++) {
            for (int x = 0; x < dim.getWidth(); x++) {
                uint8_t tileID = dim.tiles[y][x];
                Color tileColor = GetColorFromIndex(tileID);

                // Calculate screen position
                int screenX = x * tileSize;
                int screenY = y * tileSize;

                // Draw the tile as a filled rectangle
                DrawRectangle(screenX, screenY, tileSize, tileSize, tileColor);
                DrawText(std::to_string(tileID).c_str(), screenX + tileSize / 4, screenY + tileSize / 4, 10, BLACK);
            }
        }
    }
}