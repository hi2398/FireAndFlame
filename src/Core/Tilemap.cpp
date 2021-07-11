//
// Created by Ashty on 06.06.2021.
//

#include "Tilemap.h"

Tilemap::Tilemap(const std::string& tileDescription, const std::string& levelDescription) {
    std::ifstream tilesetDescriptionFile(tileDescription);
    tilesetDescription = nlohmann::json::parse(tilesetDescriptionFile);
    tilesetDescriptionFile.close();

    std::ifstream levelMapFile(levelDescription);
    this->levelDescription = nlohmann::json::parse(levelMapFile);
    levelMapFile.close();

    tileAtlasTexture = LoadTexture((tilesetDescription["image"].get<std::string>()).c_str());
    InitTileRecs();
}

void Tilemap::Draw() {
    int worldIndex{0};
    for(const auto& x : tileRecs){
        DrawTextureRec(tileAtlasTexture, x, *(tileWorldPos.begin()+worldIndex), WHITE);
        ++worldIndex;
    }
}

void Tilemap::InitTileRecs() {
    Vector2 tilemapPos = {0, 0};
    Vector2 worldPos = {0, 0};

    for (auto const &layer : levelDescription["layers"]) {
        if (layer["type"] == "tilelayer" && layer["visible"]) {
            for (auto const &tileId : layer["data"]) {
                if (tileId != 0) {
                    tilemapPos.x = (float) ((int) tileId - 1 % (int) tilesetDescription["columns"]) * (float) levelDescription["tilewidth"];
                    tilemapPos.y =  (float) floor((float) tileId / (float) tilesetDescription["columns"]) * (float) levelDescription["tilewidth"];
                    tileRecs.push_back(Rectangle{tilemapPos.x,tilemapPos.y,levelDescription["tilewidth"], levelDescription["tileheight"]});
                }
                if(tileId!=0 && layer["name"]=="collision"){
                    tileWorldPosCollision.push_back(worldPos);
                }
                if(tileId!=0) {
                    tileWorldPos.push_back(worldPos);
                }
                worldPos.x += (float) levelDescription["tilewidth"];
                if (worldPos.x >= (float) layer["width"] * (float) levelDescription["tilewidth"]) {
                    worldPos.x = 0;
                    worldPos.y += (float) levelDescription["tileheight"];
                }
            }
        }
        worldPos.x = 0;
        worldPos.y = 0;
    }
}

const std::vector<Vector2> &Tilemap::GetTileColliders() const {
    return tileWorldPosCollision;
}