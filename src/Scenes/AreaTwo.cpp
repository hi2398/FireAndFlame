#include "AreaTwo.h"

#include "AreaTwo.h"
#include "../Data/Enemies/Fly.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Enemies/Saugi.h"
#include "../Data/Enemies/SpiderBot.h"
#include "../Data/Enemies/SpringHog.h"
#include "../Data/Enemies/ToastCat.h"
#include "../Data/Enemies/Howler.h"
#include "../Data/Deathzone.h"
#include "../Data/DialogueObject.h"
#include "../Data/SaveInteractable.h"

AreaTwo::AreaTwo(SceneEnums lastScene) : Scene(SceneEnums::AreaTwo) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Two_Tilemap.json");
    Vector2 tempVec= {96*32,41*32};
    playerCharacter->active=true;
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::TraitorBoss, sceneName));

    sceneChanger = LoadTexture("assets/graphics/OtherObjects/environment.png");
    sceneChangerVec = { 97 * 32,43 * 32 };

    tempVec = {66*32,102*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {57*32,102*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {52*32,71*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {66*32,72*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {71*32,57*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {40*32,99*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Low));
    tempVec = {96*32,88*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Low));
    tempVec = {88*32,76*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Low));
    tempVec = {77*32,110*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Medium));
    tempVec = {73*32,103*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Medium));
    tempVec = {85*32,76*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Medium));
    tempVec = {71*32,103*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {39*32,99*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {62*32,103*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {69*32,90*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {92*32,112*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Medium));
    tempVec = {51*32,90*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Medium));
    tempVec = {101*32,112*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));
    tempVec = {51*32,90*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    tempVec = {109*32,114*32 + 3};
    statueTex = LoadTexture("assets/graphics/Sign.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Neutrale_Ebene_Level_12.json",tempVec,statueTex));

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


    tempVec = { 91 * 32, 97 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Left, SpawnerType::Enemy));

    tempVec = { 71 * 32, 77 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));

    tempVec = { 46 * 32, 62 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Up, SpawnerType::Coal));


    //music init
    track = LoadMusicStream("assets/audio/tracks/AreaTwo.mp3");
    SetMusicVolume(track, soundManager->GetTrackVolume());
    PlayMusicStream(track);

    //checkpoints
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointA));
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointB));
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointC));

    playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Doublejump);
}

void AreaTwo::Update() {
    UpdateMusicStream(track);
    Scene::Update();

    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Coal) {
            spawn->SpawnCoal();
        }
        if (spawn->GetType() == SpawnerType::Enemy) {
            switch (GetRandomValue(0, 4))
            {
            case 0:
                spawn->SpawnEnemy(EnemyTypes::Flyer, EnemyLevel::Low);
                break;
            case 1:
                spawn->SpawnEnemy(EnemyTypes::Howler, EnemyLevel::Low);
                break;
            case 2:
                spawn->SpawnEnemy(EnemyTypes::SpiderBot, EnemyLevel::Low);
                break;
            case 3:
                spawn->SpawnEnemy(EnemyTypes::Miner, EnemyLevel::Low);
                break;
            case 4:
                spawn->SpawnEnemy(EnemyTypes::SpringHog, EnemyLevel::Low);
                break;
            }
        }
    }
}

void AreaTwo::Draw() {
    for (const auto& spawn : spawner) {
        spawn->Draw();
    }
    DrawTextureRec(sceneChanger, { 32 * 5, 32 * 4, 32 * 3, 32 * 2 }, sceneChangerVec, WHITE);
}

AreaTwo::~AreaTwo()
{
    UnloadTexture(statueTex);
    UnloadTexture(sceneChanger);
    UnloadTexture(textureBackgroundException);
    UnloadTexture(textureBackgroundMain);
    UnloadTexture(textureForegroundException);
    UnloadTexture(textureForegroundMain);

    UnloadTexture(sceneChanger);
    StopMusicStream(track);
    UnloadMusicStream(track);
}
