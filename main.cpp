#include "raylib.h"
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void Input(float dt)
{

}

void Update(float dt)
{

}

void Draw()
{
    BeginDrawing();
    ClearBackground(WHITE);

    DrawText("This is a Raylib Starter Template for C++ Avanced Project 2026", SCREEN_WIDTH / 2 - 425, SCREEN_HEIGHT / 2 - 13, 26, BLUE);

    EndDrawing();
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Starter Template");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Input(dt);
        Update(dt);
        Draw();
    }
    CloseWindow();
    return 0;
}