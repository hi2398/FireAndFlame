#include "MinerBossScene.h"
#include "../Global.h"
#include "NeutralArea.h"
#include "../Data/MinerBoss/MinerBoss.h"

MinerBossScene::MinerBossScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placeholder_Tile_Atlas.json", "assets/Tilemaps/Miner_Boss_Tilemap.json");
    playerCharacter->SetPosition(playerStart);
    playerCharacter->SetHealth(100);
    enemies.emplace_back(std::make_unique<MinerBoss>(bossStart));
}

void MinerBossScene::Update() {
    Scene::Update();

}

void MinerBossScene::Draw() {
    Scene::Draw();
}



