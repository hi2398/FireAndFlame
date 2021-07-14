//
// Created by Ashty on 06.07.2021.
//

#include "AreaOne.h"

AreaOne::AreaOne(){
    playerCharacter->SetPosition({0, 101 * 32});
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Area_1.json");
    // Delete this section, only for testing
    Vector2 tempVec= playerCharacter->GetPosition();
    tempVec.x-=256;
    // Delete End
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec));
}

void AreaOne::Update() {

}

void AreaOne::Draw() {
    
}
