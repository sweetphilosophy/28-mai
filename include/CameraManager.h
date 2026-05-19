#pragma once
#include "raylib.h"
#include "Config.h"

struct Player; // Forward declaration to avoid circular dependency
struct Dimension; // Forward declaration to avoid circular dependency

class CameraManager {
public:
    void Init(int screenW, int screenH);
    void SetViewport(int screenW, int screenH);
    void RebuildVerticalLimits(const Dimension& dim);
    void UpdateFollow(const Player& player, const Dimension& dim);

    const Camera2D& GetCamera() const { return camera; }
    Vector2 ScreenToWorld(Vector2 screenPos) const { return GetScreenToWorld2D(screenPos, camera); }
    Vector2 WorldToScreen(Vector2 worldPos) const { return GetWorldToScreen2D(worldPos, camera); }

private:
    Camera2D camera{};
    float minTargetY = 0.0f;
    float maxTargetY = 0.0f;
    int screenW = 0;
    int screenH = 0;
};