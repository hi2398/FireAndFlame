//
// Created by Ashty on 26.07.2021.
//

#include "FBSpawnE.h"
#include "FBIdleFly.h"
#include "../../Global.h"
#include "FinalBossEnemy.h"
#include "../../Data/Enemies/Miner.h"

FBSpawnE::FBSpawnE() {
    Vector2 tempVec = {89*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {92*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {98*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {101*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));

    activeFrame = {0,64,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");

    soundManager->PlaySfx(SFX::FB_SPEECH2);
}

std::shared_ptr<State> FBSpawnE::Update(Actor &actor) {
    --waitCounter;
    if(waitCounter <= 0){
        return std::make_shared<FBIdleFly>();
    }
    if(counter == 0){
        counter = 40;
        switch ((int)activeFrame.x) {
            case 0: activeFrame = {64,64,64,64};
                break;
            case 32: activeFrame = {128,64,64,64};
                break;
            case 64: activeFrame = {0,64,64,64};
                break;
            default:
                break;

        }
    }else {counter--;}
    return shared_from_this();;
}

void FBSpawnE::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}

FBSpawnE::~FBSpawnE()
{
    UnloadTexture(bossMap);
}
