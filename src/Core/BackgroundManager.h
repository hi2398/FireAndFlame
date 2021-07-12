#pragma once
#include "raylib.h"
#include "Scene.h"
class BackgroundManager {
public:
    BackgroundManager() {};
    void SetBackgrounds(Vector2 vecFore, Vector2 vecMiddle, Vector2 vecBack);
    void Parallax();
    void Draw();
    ~BackgroundManager() = default;
protected:

private:
    //Test background
    Texture2D textureF;
    Texture2D textureM;
    Texture2D textureB;

    Vector2 tmp1 = {};
    Vector2 tmp2 = {};

    Vector2 drawFore{};
    Vector2 drawMiddle{};
    Vector2 drawBack{};

    int skipFrame = 0;
};