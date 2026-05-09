#include "DimensionManager.h"
#include <unordered_map>
#include <cmath>
#include "raylib.h"
#include "Config.h"


// fill in with preffered colors
// color code, index
static const std::unordered_map<uint32_t, int> colorCodeToIndex = {
    {0xFFFFFF, TileIndex::Air},
    {0x964B00, TileIndex::Dirt},
    {0x00FF00, TileIndex::Grass},
    {0x422109, TileIndex::Wood},
    {0x228B22, TileIndex::LeafBlock},
    {0x808080, TileIndex::Stone},
    {0xF5DEB3, TileIndex::Planks},
    {0x4B4B4B, TileIndex::Bedrock},
    {0x1E90FF, TileIndex::BlueObsidian}
};

Color GetColorFromIndex(int index) {
    switch (index) {
        case TileIndex::Air:          return GetColor(0xFFFFFFFF); // White for air (transparent)
        case TileIndex::Dirt:         return GetColor(0x964B00FF); // Raylib GetColor handles 0xRRGGBBAA
        case TileIndex::Grass:        return GetColor(0x00FF00FF);
        case TileIndex::Wood:         return GetColor(0x422109FF);
        case TileIndex::LeafBlock:    return GetColor(0x228B22FF);
        case TileIndex::Stone:        return GetColor(0x808080FF);
        case TileIndex::Planks:       return GetColor(0xF5DEB3FF);
        case TileIndex::Bedrock:      return GetColor(0x4B4B4BFF);
        case TileIndex::BlueObsidian: return GetColor(0x1E90FFFF);
        default:                      return WHITE; // Or any "error" color
    }
}

const char* Dimension::GetNameFromID(int tileID) const {
    switch (tileID) {
        case TileIndex::Air:          return "Air";
        case TileIndex::Dirt:         return "Dirt";
        case TileIndex::Grass:        return "Grass";
        case TileIndex::Wood:         return "Wood";
        case TileIndex::LeafBlock:    return "LeafBlock";
        case TileIndex::Stone:        return "Stone";
        case TileIndex::Planks:       return "Planks";
        case TileIndex::Bedrock:      return "Bedrock";
        case TileIndex::BlueObsidian: return "BlueObsidian";
        default:                      return "Unknown";
    }
}

void Dimension::LoadFromFile(std::string filename) {
    // 1. Load the image into CPU memory
    Image mapImage = LoadImage(filename.c_str());
    
    if (mapImage.data == nullptr) {
        // TraceLog(LOG_ERROR, "Failed to load map image: %s", filename.c_str());
        return;
    }

    // 2. Initialise 2D vector size
    // tiles[y][x] structure
    tiles.assign(mapImage.height, std::vector<int>(mapImage.width, static_cast<int>(TileIndex::Air)));

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
                tiles[y][x] = static_cast<int>(TileIndex::Air);
            }
        }
    }

    // 5. Unload image from CPU memory (very important!)
    UnloadImage(mapImage);
    
    // TraceLog(LOG_INFO, "Dimension loaded: %i x %i tiles", mapImage.width, mapImage.height);
}

// filename should include extension, e.g. "my_map.png". 
// the output folder is the same as the executable
void Dimension::SaveToFile(std::string filename) const {
    // 1. Check if the vector is empty to avoid crashes
    if (tiles.empty() || tiles[0].empty()) {
        // TraceLog(LOG_WARNING, "Cannot save dimension: tiles vector is empty.");
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
            int tileID = tiles[y][x];

            // Get the corresponding color
            Color tileColor = GetColorFromIndex(tileID);

            // Draw the pixel onto our image data
            ImageDrawPixel(&mapImage, x, y, tileColor);
        }
    }

    // 4. Export the image to a file
    // Raylib supports .png, .bmp, .tga, .jpg automatically based on extension
    if (ExportImage(mapImage, filename.c_str())) {
        // TraceLog(LOG_INFO, "Dimension successfully saved to: %s", filename.c_str());
    } else {
        // TraceLog(LOG_ERROR, "Failed to export dimension image: %s", filename.c_str());
    }

    // 5. Clean up the temporary image data
    UnloadImage(mapImage);
}

int Dimension::getWidth() const {
    return (tiles.empty()) ? 0 : tiles[0].size();
}

int Dimension::getHeight() const {
    return tiles.size();
}

int Dimension::WrapX(int x) const {
    int width = getWidth();
    if (width <= 0) {
        return x;
    }

    int wrapped = x % width;
    if (wrapped < 0) {
        wrapped += width;
    }
    return wrapped;
}

Dimension::Dimension(std::string filename, bool isActive) : isActive(isActive) {
    LoadFromFile(filename);
}

bool Dimension::inBounds(int x, int y) const {
    return y >= 0 && y < (int)tiles.size() && x >= 0 && x < (int)tiles[y].size();
}

bool Dimension::inBounds(std::pair<int, int> pos) const {
    return inBounds(pos.first, pos.second);
}

void Dimension::Update() {
    // Process pending updates in the queue
    for (int i = 0; i < updatesPerFrame && !updateQueue.empty(); i++) {
        Action action = updateQueue.front();
        updateQueue.pop();

        int x = action.position.first;
        int y = action.position.second;

        // Validate coordinates
        if (inBounds(action.position)) {
            tiles[y][x] = action.newTileID;
            // TraceLog(LOG_INFO, "Tile updated at (%i, %i) to ID %i", x, y, action.newTileID);
        } else {
            // TraceLog(LOG_WARNING, "Invalid tile update position: (%i, %i)", x, y);
        }
    }
}

void Dimension::Draw() const {
    // This function can be used for more complex drawing logic in the future
    // For now, tile drawing is handled in DimensionManager::Draw_MapDebug()
}

void Dimension::Draw_MapDebug(const CameraManager& cameraManager) const {
    const Camera2D& camera = cameraManager.GetCamera();
    int screenW = GetScreenWidth();
    float zoom = (camera.zoom <= 0.0f) ? 1.0f : camera.zoom;
    int mapWidthPx = getWidth() * tileWidth;

    float halfViewW = (screenW * 0.5f) / zoom;
    int centerCopy = (int)std::floor(camera.target.x / mapWidthPx);
    int copiesEachSide = (int)std::ceil(halfViewW / mapWidthPx) + 1;

    for (int copy = centerCopy - copiesEachSide; copy <= centerCopy + copiesEachSide; ++copy) {
        DrawIndividualMap(cameraManager, (float)copy * mapWidthPx);
    }
}

const Dimension& DimensionManager::GetCurrentDimension() const {
    // if (dimensions.empty()) {
    //     throw std::runtime_error("No dimensions available.");
    // }
    // if (currentDimensionIndex < 0 || currentDimensionIndex >= (int)dimensions.size()) {
    //     throw std::out_of_range("Current dimension index is out of bounds.");
    // }
    return dimensions[currentDimensionIndex];
}

Dimension& DimensionManager::GetCurrentDimension() {
    // if (dimensions.empty()) {
    //     throw std::runtime_error("No dimensions available.");
    // }
    // if (currentDimensionIndex < 0 || currentDimensionIndex >= (int)dimensions.size()) {
    //     throw std::out_of_range("Current dimension index is out of bounds.");
    // }
    return dimensions[currentDimensionIndex];
}

void Dimension::DrawIndividualMap(const CameraManager& cameraManager, float offsetX) const {
    // quick and dirty: special debug button to draw the tile IDs for testing

    static bool showTileIDs = false;
    if (IsKeyPressed(KEY_TAB)) {
        showTileIDs = !showTileIDs;
    }

    for (int y = 0; y < getHeight(); y++) {
        for (int x = 0; x < getWidth(); x++) {
            int tileID = tiles[y][x];
            Color tileColor = GetColorFromIndex(tileID);
            DrawRectangle((int)(offsetX + x * tileWidth), y * tileHeight, tileWidth, tileHeight, tileColor);
            if (showTileIDs) {
                DrawText(TextFormat("%i", tileID), (int)(offsetX + x * tileWidth + 10), y * tileHeight + 10, 10, BLACK);
            }
        }
    }
}

void DimensionManager::Update() {
    // Placeholder for any future updates (e.g., animations, dynamic changes)
    for (Dimension& dim : dimensions) {
        if (!dim.isActive) {
            continue; // Skip inactive dimensions
        }

        // Update logic for active dimensions can be added here
        dim.Update();
    }
}

void DimensionManager::Draw() const {
    // Placeholder for any future updates
    // pass through dimension map vector, see id, place texture for that id at the right place
}

void DimensionManager::Draw_MapDebug(const CameraManager& cameraManager) const {

    if (dimensions.empty()) {
        // TraceLog(LOG_WARNING, "No dimensions to draw.");
        return;
    }

    if (currentDimensionIndex < 0 || currentDimensionIndex >= (int)dimensions.size()) {
        // TraceLog(LOG_ERROR, "Current dimension index out of bounds: %i", currentDimensionIndex);
        return;
    }

    for (int i = 0; i < (int)dimensions.size(); i++) {
        const Dimension& dim = dimensions[i];
        if (!dim.isActive) {
            continue; // Skip inactive dimensions
        }

        if (dim.tiles.empty() || dim.tiles[0].empty()) {
            continue;
        }

        dim.Draw_MapDebug(cameraManager);
    }
} 