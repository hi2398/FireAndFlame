#include "IceBossScene.h"
#include "../Global.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/IceBoss/IceZone.h"
#include "../Data/Deathzone.h"
#include "../Data/PowerUp.h"
#include "../Data/SaveInteractable.h"

IceBossScene::IceBossScene(SceneEnums lastScene) : Scene(SceneEnums::IceBoss) {
    this->lastScene = lastScene;
    playerCharacter->active=true;
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json", "assets/Tilemaps/Ice_Boss_Tilemap.json");
    playerCharacter->SetPosition(playerStart);
    playerCharacter->SetHealth(100);
    Vector2 tempVec = {19*32, 48*32};
    tilemap->AddCollisionTile(tempVec);
    tempVec = {19*32, 47*32};
    tilemap->AddCollisionTile(tempVec);
    tempVec = { 48 * 32, 33 * 32 };
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec, SceneEnums::NeutralArea, sceneName));
    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    textureForegroundException = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_01_bottom.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_01_sides.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_02.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_02.png");

    sceneChanger = LoadTexture("assets/graphics/OtherObjects/environment.png");
    sceneChangerVec = { 46 * 32, 33 * 32 };

    foregroundPos = { -32*8, -90 };
    backgroundPos = { -32*8,0 };

    //fill background loop vector
    backgroundLoopX = 8;
    backgroundLoopY = 16;
    backgroundException = 0;

    foregroundLoopX = 4;
    foregroundLoopY = 8;
    foregroundException = 7;

    tempVec = { 26 * 32, 27 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));
    tempVec = { 31 * 32, 27 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));

    //checkpoints
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointA));

    track = LoadMusicStream("assets/audio/tracks/iceboss.mp3");
    SetMusicVolume(track, soundManager->GetTrackVolume());

}


void IceBossScene::Update() {
    if (blockedPath.y <= 47*32) blockedPath.y += 10;
    if (blockedPath.y >= 47 * 32) {
        if (!boulderPlaced) {
            sceneManager->ScreenShake(45);
            soundManager->PlaySfx(SFX::DOORS);
            boulderPlaced = true;
        }
    }
    if (bossActivated && !bossDefeated)UpdateMusicStream(track);
    Scene::Update();
    if (!bossActivated) {
        //When player enters boss Arena, close entrance and exit and spawn Boss
        if (CheckCollisionRecs(bossSpawnTrigger, playerCharacter->playerHitbox)) {
            bossActivated=true;
            hud->IsBossFightActive(true);
            enemies.emplace_back(std::make_unique<IceBoss>(bossSpawnPoint));
            PlayMusicStream(track);
            for (const auto& loc : blockadeColliders) {
                tilemap->AddCollisionTile(loc);
            }
        }
    }

    if (bossActivated && !bossDefeated) {
        BossDeath(); //evaluates if boss is alive, auto cleanups if dead (removes blockades etc)
    }

    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Coal) {
            spawn->SpawnCoal();
        }
    }

}

void IceBossScene::Draw() {
    DrawTexturePro(sceneChanger, { 0,0,32,32 }, { blockedPath.x, blockedPath.y, 64, 64 }, {0}, 0.0, WHITE);
    if (bossActivated && !bossDefeated) {
        DrawTextureEx(entrance.texture, entrance.location, entrance.rotation, 1, WHITE);
        DrawTextureEx(exit.texture, exit.location, exit.rotation, 1, WHITE);
    }
    for (const auto& spawn : spawner) {
        spawn->Draw();
    }

    DrawTextureRec(sceneChanger, {32, 0, 32 * 4, 32 * 4}, sceneChangerVec, WHITE);
}

bool IceBossScene::BossDeath() {

    //search if boss exists
    for (const auto &enemy : enemies) { //if boss still exists, return true
        if (enemy->GetEnemyType() == EnemyTypes::Boss) return true;
    }
    //if not found, he is not alive, remove the blockades and set bool to true
    Vector2 tempVec = { 39 * 32, (37 * 32)-16 };
    interactables.emplace_back(std::make_unique<PowerUp>(tempVec, PowerUpType::dash));
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    tilemap->RemoveCollisionTile();
    StopMusicStream(track);
    hud->IsBossFightActive(false);
    bossDefeated=true;
    return false;
}

IceBossScene::~IceBossScene() {
    UnloadTexture(textureBackgroundException);
    UnloadTexture(textureBackgroundMain);
    UnloadTexture(textureForegroundException);
    UnloadTexture(textureForegroundMain);
    UnloadTexture(sceneChanger);

    UnloadMusicStream(track);
}