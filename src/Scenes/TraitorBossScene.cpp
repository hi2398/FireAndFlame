
#include "TraitorBossScene.h"
#include "../Global.h"


TraitorBossScene::TraitorBossScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json", "assets/Tilemaps/Verrater_Boss_neu.json");
    playerCharacter->SetPosition(playerStart);
    playerCharacter->SetHealth(100);
}

void TraitorBossScene::Update() {
    Scene::Update();

}

void TraitorBossScene::Draw() {
    Scene::Draw();
}