//
// Created by Ashty on 06.07.2021.
//

#include "AreaOne.h"

AreaOne::AreaOne(){
    playerCharacter->SetPosition({19*32, 107 * 32});
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_One_Tilemap.json");
    Vector2 tempVec= {47*25,29*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::MinerBoss));
}

void AreaOne::Update() {

}

void AreaOne::Draw() {
    
}
