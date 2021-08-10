//
// Created by Ashty on 06.07.2021.
//

#include "AreaOne.h"

AreaOne::AreaOne(){
    playerCharacter->SetPosition({0, 101 * 32});
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placeholder_Tile_Atlas.json","assets/Tilemaps/Area_One_Tilemap.json");
    Vector2 tempVec= {32*25,32*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::MinerBoss));
}

void AreaOne::Update() {

}

void AreaOne::Draw() {
    
}
