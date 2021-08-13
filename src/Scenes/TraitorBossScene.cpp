#include "TraitorBossScene.h"

#include "TraitorBossScene.h"
#include "../Global.h"
#include "../Data/TraitorBoss/TraitorBoss.h"
#include "../Data/Coal.h"


TraitorBossScene::TraitorBossScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json", "assets/Tilemaps/Verrater_Boss_neu.json");
    playerCharacter->SetPosition(playerStart);

    playerCharacter->SetHealth(100);
    
    door1[0] = { 49 * 32, 87 * 32 };
    door1[1] = { 49 * 32, 88 * 32 };

    door2[0] = { 68 * 32, 87 * 32 };
    door2[1] = { 68 * 32, 88 * 32 };


    Vector2 tmp1 = { 51 * 32, 88 * 32 };
    Vector2 tmp2 = { 65 * 32, 88 * 32 };
    Vector2 tmp3 = { 52 * 32, 88 * 32 };
    interactables.emplace_back(std::make_unique<Coal>(tmp1));
    interactables.emplace_back(std::make_unique<Coal>(tmp2));
    interactables.emplace_back(std::make_unique<Coal>(tmp3));

}

void TraitorBossScene::Update() {
    Scene::Update();
    if (bossActivated && !bossDefeated)CheckBossDeath();

    if (playerCharacter->GetPosition().x >= 51 * 32 && playerCharacter->GetPosition().y <= 88 * 32 && !bossActivated && !bossDefeated) {
        tilemap->AddCollisionTile({door1[0]});
        tilemap->AddCollisionTile({ door1[1] });
        tilemap->AddCollisionTile({ door2[0] });
        tilemap->AddCollisionTile({ door2[1] });
        doorActive = true;
        bossActivated = true;
        enemies.emplace_back(std::make_unique<TraitorBoss>(bossSpawn));
    }
}

void TraitorBossScene::Draw() {
    Scene::Draw();

    if (doorActive) {
		DrawRectangle(door1[0].x, door1[0].y, 32, 64, RED);
        DrawRectangle(door2[0].x, door2[0].y, 32, 64, RED);
    }
    
}

void TraitorBossScene::CheckBossDeath()
{
    //search if boss exists
    for (const auto& enemy : enemies) { //if boss still exists, return true
        if (enemy->GetEnemyType() == EnemyTypes::Boss) {
            return;
        }
    }
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    bossDefeated = true;
    doorActive = false;
    return;
}
