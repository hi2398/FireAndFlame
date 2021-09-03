#include "MinerBossScene.h"
#include "MinerBossScene.h"
#include "raymath.h"
#include "../Global.h"
#include "NeutralArea.h"
#include "../Data/MinerBoss/MinerBoss.h"
#include "../Data/Deathzone.h"

MinerBossScene::MinerBossScene(SceneEnums lastScene) : Scene(SceneEnums::MinerBoss) {
    this->lastScene = lastScene;
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json", "assets/Tilemaps/Miner_Boss_Tilemap.json");
    playerCharacter->SetPosition(playerStart);
    playerCharacter->SetHealth(100);
    debrisTexture = LoadTexture("assets/Bosses/MinerBoss/debris.png");

    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/AreaOne/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/AreaOne/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/AreaOne/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/AreaOne/background.png");

    foregroundPos = { 0,-100 };
    backgroundPos = { 0,0 };

    //fill background loop vector
    backgroundLoopX = 8;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 4;
    foregroundLoopY = 9;
    foregroundException = 8;

    Vector2 tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    tempVec = { 47 * 32, 82 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));

    tempVec = { 59 * 32, 82 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));

    tempVec = { 48 * 32, 51 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));

    tempVec = { 57 * 32, 51 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));
}

void MinerBossScene::Update() {
    Scene::Update();
    if (!bossActivated){
        if (Vector2Distance(playerCharacter->GetPosition(), {47*32, 90*32})<32) {
            enemies.emplace_back(std::make_unique<MinerBoss>(bossStart));
            bossActivated= true;
        }
    }

    if (!bossDefeated) OnBossDeath();

    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Coal) {
            spawn->SpawnCoal();
        }
    }
}

void MinerBossScene::Draw() {
    Scene::Draw();
    if (lowerDebrisEnabled){
        DrawTextureV(debrisTexture, lowerDebrisLoc, WHITE);
    }
    if (upperDebrisEnabled){
        DrawTextureV(debrisTexture, upperDebrisLocA, WHITE);
        DrawTextureV(debrisTexture, upperDebrisLocB, WHITE);
        DrawTextureV(debrisTexture, upperDebrisLocC, WHITE);
        DrawTextureV(debrisTexture, upperDebrisLocD, WHITE);
        DrawTextureV(debrisTexture, upperDebrisLocE, WHITE);
    }
    for (const auto& spawn : spawner) {
        spawn->Draw();
    }
}

void MinerBossScene::EnableDebrisLower() {
    lowerDebrisEnabled= true;
}

void MinerBossScene::EnableDebrisUpper() {
    upperDebrisEnabled=true;
    sceneManager->GetTilemap()->AddCollisionTile(upperDebrisLocA);
    sceneManager->GetTilemap()->AddCollisionTile(upperDebrisLocB);
    sceneManager->GetTilemap()->AddCollisionTile(upperDebrisLocC);
    sceneManager->GetTilemap()->AddCollisionTile(upperDebrisLocD);
    sceneManager->GetTilemap()->AddCollisionTile(upperDebrisLocE);
}

void MinerBossScene::OnBossDeath()
{
    if (bossActivated) {
        for (const auto& enemy : sceneManager->GetEnemies()) {
            if (enemy->GetEnemyType() == EnemyTypes::Boss) return;
        }
    }

    //functions on boss death
    bossDefeated = true;
    playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Doublejump);
    return;
}



