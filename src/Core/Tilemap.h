#pragma once
#include <fstream>
#include "../json.hpp"
#include "raylib.h"
#include <vector>

class Tilemap {
public:
    explicit Tilemap(const std::string& tileDescription, const std::string& levelDescription);

    void Draw();
protected:

private:
    nlohmann::json tilesetDescription;
    nlohmann::json levelDescription;
    Texture2D tileAtlasTexture;
    std::vector<Rectangle> tileRecs; // Collider for the Tile
    std::vector<Vector2> tileWorldPos;
    void InitTileRecs(); // Creates once a Rectangle for every Tile for performance issues
};

