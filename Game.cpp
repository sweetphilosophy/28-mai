#include "Game.h"
#include "raylib.h"
#include "Player.h"

Game::Game() {
    InitWindow(800, 600, "Entity Test");
    SetTargetFPS(60);
}

void Game::run() {
    Player player;
    player.hitbox = { 400, 300, 40, 40 };
    player.hp = 100;
    player.dmg = 10;
    player.speed = 5.0f;
    player.id = 0;

    while (!WindowShouldClose()) {
        player.HandleMovement();
        player.HandleMouse();
        player.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        player.DrawDebug();
        EndDrawing();
    }

    CloseWindow();
}
