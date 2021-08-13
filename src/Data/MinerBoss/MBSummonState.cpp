#include "MBSummonState.h"
#include "MinerBoss.h"

MBSummonState::MBSummonState(Enemy &enemy) : EState(enemy) {

}

std::shared_ptr<EState> MBSummonState::Update(Enemy &actor) {
    return shared_from_this();
}

void MBSummonState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}
