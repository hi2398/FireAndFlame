//
// Created by Ashty on 06.07.2021.
//

#include "AreaOne.h"

AreaOne::AreaOne() : Scene("assets/Dialogues/testText.json"){
    playerCharacter->SetPosition({0, 101 * 32});
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Area_1.json");
    interactables.emplace_back(std::make_unique<Coal>(playerCharacter->GetPosition()));
}

void AreaOne::Update() {

}

void AreaOne::Draw() {

}
