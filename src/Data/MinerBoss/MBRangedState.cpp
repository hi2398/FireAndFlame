#include "MBRangedState.h"
#include "MinerBoss.h"
#include "MBDecisionState.h"
#include "../../Global.h"

MBRangedState::MBRangedState(Enemy &enemy) : EState(enemy) {
    if constexpr(DEBUG_ENEMY_STATES){
        std::cout << "Miner Boss State Transition to: Ranged\n";
    }
}

std::shared_ptr<EState> MBRangedState::Update(Enemy &actor) {
    --timer;


    if (timer==0){
        return std::make_shared<MBDecisionState>(actor);
    }
    return shared_from_this();
}

void MBRangedState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}
