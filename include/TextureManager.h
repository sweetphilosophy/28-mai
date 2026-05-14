#pragma once
#include "Config.h"
#include "raylib.h"
#include <vector>

struct TextureManager{
public:
    TextureManager();
    ~TextureManager();
    void Init();
    Texture2D GetTextureForTileID(int tileID) const;
    
private:    
    void LoadTextures();
    bool texturesLoaded = false;
    std::vector<Texture2D> tileTextures;
};