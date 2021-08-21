#include "IceBossScene.h"
#include "../Global.h"
#include "../Data/IceBoss/IceZone.h"

IceBossScene::IceBossScene() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json", "assets/Tilemaps/Ice_Boss_Tilemap.json");
    playerCharacter->SetPosition(playerStart);
    playerCharacter->SetHealth(100);
    Vector2 tempVec = {19*32, 48*32};
    tilemap->AddCollisionTile(tempVec);
    tempVec = {19*32, 47*32};
    tilemap->AddCollisionTile(tempVec);
}


void IceBossScene::Update() {

    if (!bossActivated) {
        //When player enters boss Arena, close entrance and exit and spawn Boss
        if (CheckCollisionRecs(bossSpawnTrigger, playerCharacter->playerHitbox)) {
            bossActivated=true;
            enemies.emplace_back(std::make_unique<IceBoss>(bossSpawnPoint));
            for (const auto& loc : blockadeColliders) {
                tilemap->AddCollisionTile(loc);
            }
        }
    }

    if (bossActivated && !bossDefeated) {
        BossDeath(); //evaluates if boss is alive, auto cleanups if dead (removes blockades etc)
    }



}

void IceBossScene::Draw() {
    if (bossActivated && !bossDefeated) {
        DrawTextureEx(entrance.texture, entrance.location, entrance.rotation, 1, WHITE);
        DrawTextureEx(exit.texture, exit.location, exit.rotation, 1, WHITE);
    }
}

bool IceBossScene::BossDeath() {

    //search if boss exists
    for (const auto &enemy : enemies) { //if boss still exists, return true
        if (enemy->GetEnemyType() == EnemyTypes::Boss) return true;
    }
    //if not found, he is not alive, remove the blockades and set bool to true
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    bossDefeated=true;
    return false;
}

