#include "IceBossScene.h"
#include "../Global.h"

IceBossScene::IceBossScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json", "assets/Tilemaps/Ice_Boss_Tilemap.json");
    playerCharacter->SetPosition(playerStart);
}

void IceBossScene::Update() {

}

void IceBossScene::Draw() {

}

