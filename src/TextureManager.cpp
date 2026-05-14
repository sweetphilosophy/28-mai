#include "TextureManager.h"
#include <string>

TextureManager::TextureManager() {
}

void TextureManager::Init() {
    if (!texturesLoaded) {
        LoadTextures();
        texturesLoaded = true;
    }
}

Texture2D TextureManager::GetTextureForTileID(int tileID) const {
    if (tileID < 0 || static_cast<size_t>(tileID) >= tileTextures.size()) {
        // Return a default texture or handle error as needed
        return tileTextures[0]; // return the "no_texture.png" as a fallback
    }
    return tileTextures[tileID];
}

void TextureManager::LoadTextures() {
    tileTextures.reserve(TileIndex::TileCount);
    for (int i = 0; i < TileIndex::TileCount; i++) {
        std::string filepath = std::string(staticTextureDirectory) + "\\" + staticTexturesFilenames[i];
        Image img = LoadImage(filepath.c_str());
        if (img.data == nullptr) {
            // Handle loading error, e.g., log and continue with a placeholder texture
            TraceLog(LOG_ERROR, "Failed to load texture: %s", filepath.c_str());
            // tileTextures.push_back(LoadTextureFromImage(LoadImage("assets/sprites/static/no_texture.png")));
        } else {
            tileTextures.push_back(LoadTextureFromImage(img));
            UnloadImage(img); // We can unload the image after creating the texture
        }
    }
}

TextureManager::~TextureManager() {
    for (Texture2D& tex : tileTextures) {
        UnloadTexture(tex);
    }
}