#pragma once

#include "raylib.h"
#include "Player.h"
#include "DimensionManager.h"

struct ObjectManager {

    ObjectManager();

    void Input(DimensionManager& dimManager);
    void Update(DimensionManager& dimManager, float dt);
    void Draw();
    void DrawDebug() const;

    Player player;
};