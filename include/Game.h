#pragma once

#include "raylib.h"

class Game {

    void RunGame();

private:
    void Input(float dt);
    void Update(float dt);
    void Draw();

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
};