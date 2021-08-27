#include "MinerBossScene.h"
#include "../Global.h"
#include "NeutralArea.h"
#include "../Data/MinerBoss/MinerBoss.h"

MinerBossScene::MinerBossScene(SceneEnums lastScene) : Scene(SceneEnums::MinerBoss) {
    this->lastScene = lastScene;
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json", "assets/Tilemaps/Miner_Boss_Tilemap.json");
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



