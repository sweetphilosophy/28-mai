#pragma once

#include "raylib.h"
#include "DimensionManager.h"
#include "ObjectManager.h"
#include "Config.h"

class Game {
private:

    void Input(float dt);
    void Update(float dt);
    void Draw();

    DimensionManager dimensionManager;
    ObjectManager objectManager;

public:
    void run();
    Game();
};