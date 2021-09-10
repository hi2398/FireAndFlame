#include "AreaThree.h"

#include "AreaThree.h"
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

AreaThree::AreaThree(SceneEnums lastScene) : Scene(SceneEnums::AreaThree) {
    this->lastScene = lastScene;
    playerCharacter->SetHealth(100);
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active=true;
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Three_Tilemap.json");
    Vector2 tempVec= {80*25,17*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::FinalBoss, sceneName));

    sceneChanger = LoadTexture("assets/graphics/OtherObjects/environment.png");
    sceneChangerVec = { 80 * 25,20 * 26 };

    tempVec = {50*32,96*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {58*32,92*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {65*32,92*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {81*32,89*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {39*32,112*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Medium));
    tempVec = {48*32,55*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Medium));
    tempVec = {51*32,55*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Medium));
    tempVec = {47*32,99*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::High));
    tempVec = {88*32,77*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::High));
    tempVec = {81*32,94*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {81*32,94*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {73*32,90*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {64*32,71*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {43*32,68*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Medium));
    tempVec = {91*32,89*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));
    tempVec = {52*32,68*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    tempVec = {28*32,112*32};
    Texture2D statueTex = LoadTexture("assets/graphics/Sign.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Area_3Sign.json",tempVec,statueTex));

    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/AreaThree/Upper_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/AreaThree/Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/AreaThree/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/AreaThree/background.png");

    foregroundPos = { 0,1100 };
    backgroundPos = { 0,0 };

    //fill background loop vector
    backgroundLoopX = 10;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 5;
    foregroundLoopY = 9;
    foregroundException = 0;

    tempVec = { 89 * 32, 96 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Left, SpawnerType::Enemy));

    tempVec = { 44 * 32, 74 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Right, SpawnerType::Enemy));

    tempVec = { 48 * 32, 51 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Enemy));

    //music init
    track = LoadMusicStream("assets/audio/tracks/AreaThree.mp3");
    PlayMusicStream(track);

    //checkpoints
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointA));
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointB));


}

void AreaThree::Update() {
    Scene::Update();
    UpdateMusicStream(track);

    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Enemy && sceneManager->GetEnemies().size() < 25) {
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

void AreaThree::Draw() {
    for (const auto& spawn : spawner) {
        spawn->Draw();
    }
    DrawTexturePro(sceneChanger, { 32 * 5, 32 * 4, 32 * 3, 32 * 2 }, { sceneChangerVec.x - 16, sceneChangerVec.y, 32 * 5, 32 * 2 }, {}, 0.0, WHITE);
}

AreaThree::~AreaThree()
{
    StopMusicStream(track);
    UnloadMusicStream(track);
}
