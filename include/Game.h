#pragma once

#include "raylib.h"
#include "include/HandleDimensions.h"

struct Game {

    void run();

private:
    void Input(float dt);
    void Update(float dt);
    void Draw();

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    HandleDimensions handleDimensions;
};