#include "FBChangeStates.h"
#include "FBIdleDown.h"
#include "FinalBossEnemy.h"

FBChangeStates::FBChangeStates() {
    activeFrame = {0,128,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

std::shared_ptr<State> FBChangeStates::Update(Actor &actor) {
    if(counter <= 0){
        return std::make_shared<FBIdleDown>();
    }else{
        switch(counter){
            case 240: activeFrame = {64,128,64,64};
                break;
            case 220: activeFrame = {128,128,64,64};
                break;
            case 200: activeFrame = {192,128,64,64};
                break;
            case 180: activeFrame = {256,128,64,64};
                break;
            case 160: activeFrame = {320,128,64,64};
                break;
            case 140: activeFrame = {0,192,64,64};
                break;
            case 120: activeFrame = {64,192,64,64};
                break;
            case 100: activeFrame = {128,192,64,64};
                break;
            case 80: activeFrame = {192,192,64,64};
                break;
            case 60: activeFrame = {256,192,64,64};
                break;
            case 40: activeFrame = {320,192,64,64};
                break;
        }
    }
    counter--;
    return shared_from_this();;
}

void FBChangeStates::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}
