//
// Created by Ashty on 26.07.2021.
//

#include "FBFlyDown.h"
#include "FBSpawnE.h"
#include "FinalBossEnemy.h"

FBFlyDown::FBFlyDown() {
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
    activeFrame = {0,64,64,64};
}

std::shared_ptr<State> FBFlyDown::Update(Actor &actor) {
    --waitCounter;
    actor.SetPosition({94*32,76*32});
    if(waitCounter <= 0){
        return std::make_shared<FBSpawnE>();
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

void FBFlyDown::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}

FBFlyDown::~FBFlyDown()
{
    UnloadTexture(bossMap);
}
