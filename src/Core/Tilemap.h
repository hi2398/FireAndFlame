#pragma once
#include <fstream>
#include "../json.hpp"
#include "raylib.h"
#include <vector>

class Tilemap {
public:
    explicit Tilemap(const std::string& tileDescription, const std::string& levelDescription);
    Tilemap() = default;
    [[nodiscard]] const std::vector<Vector2> &GetTileColliders() const;
    void AddCollisionTile(Vector2 loc);
    void RemoveCollisionTile();
    void Draw();
protected:

private:
    nlohmann::json tilesetDescription;
    nlohmann::json levelDescription;
    Texture2D tileAtlasTexture{};
    std::vector<Rectangle> tileRecs; // All Tiles
    std::vector<Vector2> tileWorldPos; // Position of all Tiles
    std::vector<Vector2> tileWorldPosCollision; // Position of Tiles with Collision
    void InitTileRecs(); // Creates once a Rectangle for every Tile for performance issues
};