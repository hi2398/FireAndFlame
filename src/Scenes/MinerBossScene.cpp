#include "MinerBossScene.h"
#include "../Global.h"

MinerBossScene::MinerBossScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placeholder_Tile_Atlas.json", "assets/Tilemaps/Miner_Boss_Tilemap.json");
    playerCharacter->SetPosition(playerStart);
    playerCharacter->SetHealth(100);
}

void MinerBossScene::Update() {
    Scene::Update();
}

void MinerBossScene::Draw() {
    Scene::Draw();
}


