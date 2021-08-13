#include "MBRangedState.h"
#include "MinerBoss.h"

MBRangedState::MBRangedState(Enemy &enemy) : EState(enemy) {

}

std::shared_ptr<EState> MBRangedState::Update(Enemy &actor) {
    return shared_from_this();
}

void MBRangedState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}
