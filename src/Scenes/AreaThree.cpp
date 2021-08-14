
#include "AreaThree.h"

AreaThree::AreaThree(){
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Three_Tilemap.json");
    Vector2 tempVec= {80*25,24*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::FinalBoss));
}

void AreaThree::Update() {

}

void AreaThree::Draw() {

}
