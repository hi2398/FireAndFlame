
#include "AreaThree.h"

AreaThree::AreaThree(){
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Three_Tilemap.json");
}

void AreaThree::Update() {

}

void AreaThree::Draw() {

}
