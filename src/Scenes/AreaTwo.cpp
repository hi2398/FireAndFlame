
#include "AreaTwo.h"

AreaTwo::AreaTwo(){
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Two_Tilemap.json");
    Vector2 tempVec= {82*32,23*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::TraitorBoss));
}

void AreaTwo::Update() {

}

void AreaTwo::Draw() {

}
