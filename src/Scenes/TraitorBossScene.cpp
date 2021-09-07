#include "TraitorBossScene.h"

#include "TraitorBossScene.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/Spawner.h"
#include "../Global.h"
#include "../Data/TraitorBoss/TraitorBoss.h"
#include "../Data/Coal.h"
#include "../Data/Deathzone.h"
#include "../Data/PowerUp.h"


TraitorBossScene::TraitorBossScene(SceneEnums lastScene) : Scene(SceneEnums::TraitorBoss) {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/overworldTileset.json", "assets/Tilemaps/Verrater_Boss.json");
    playerCharacter->SetPosition(playerStart);

    playerCharacter->SetHealth(100);
    
    door1[0] = { 49 * 32, 87 * 32 };
    door1[1] = { 49 * 32, 88 * 32 };

    door2[0] = { 68 * 32, 87 * 32 };
    door2[1] = { 68 * 32, 88 * 32 };

    Vector2 tempVec = {93 * 32, 64 * 32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec, SceneEnums::NeutralArea, sceneName));
    tempVec = {51 * 32, 74 * 32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));
    tempVec = { 65 * 32, 74 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));

    sceneChanger = LoadTexture("assets/graphics/OtherObjects/environment.png");
    sceneChangerVec = { 91 * 32, 64 * 32 };

    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/AreaTwo/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/AreaTwo/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/AreaTwo/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/AreaTwo/background.png");

    foregroundPos = { 0,0 };
    backgroundPos = { 0,0 };

    //fill background loop vector
    backgroundLoopX = 10;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 5;
    foregroundLoopY = 9;
    foregroundException = 8;

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));
}

void TraitorBossScene::Update() {
    Scene::Update();
    if (bossActivated && !bossDefeated)CheckBossDeath();

    if (playerCharacter->GetPosition().x >= 50 * 32 && playerCharacter->GetPosition().y <= 88 * 32 && !doorActive) {
        sceneManager->ScreenShake(20);
        soundManager->PlaySfx(SFX::DOORS);
        doorActive = true;
		tilemap->AddCollisionTile({ door1[0] });
		tilemap->AddCollisionTile({ door1[1] });
		tilemap->AddCollisionTile({ door2[0] });
		tilemap->AddCollisionTile({ door2[1] });
    }
    if (playerCharacter->GetPosition().x >= 56 * 32 && playerCharacter->GetPosition().y <= 88 * 32 && !bossActivated && !bossDefeated) {
        bossActivated = true;
        enemies.emplace_back(std::make_unique<TraitorBoss>(bossSpawn));
    }

    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Coal) {
            spawn->SpawnCoal();
        }
    }

}

void TraitorBossScene::Draw() {
    Scene::Draw();

    if (doorActive && !bossDefeated) {
		DrawRectangle(door1[0].x, door1[0].y, 32, 64, RED);
        DrawRectangle(door2[0].x, door2[0].y, 32, 64, RED);
    }
    
    for (const auto& spawn : spawner) {
        spawn->Draw();
    }

    DrawTextureRec(sceneChanger, { 32 * 1, 0, 32 * 4, 32 * 4 }, sceneChangerVec, WHITE);
}

void TraitorBossScene::CheckBossDeath()
{
    //search if boss exists
    for (const auto& enemy : enemies) { //if boss still exists, return true
        if (enemy->GetEnemyType() == EnemyTypes::Boss) {
            return;
        }
    }
    Vector2 tempVec = { 70 * 32, 89 * 32-16 };
    interactables.emplace_back(std::make_unique<PowerUp>(tempVec, PowerUpType::doubleJump));
    soundManager->PlaySfx(SFX::DOORS);
    sceneManager->ScreenShake(20);
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    bossDefeated = true;
    return;
}
