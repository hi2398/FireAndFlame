
#include "AreaTwo.h"

AreaTwo::AreaTwo(){
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Two_Tilemap.json");
}

void AreaTwo::Update() {

}

void AreaTwo::Draw() {

}
