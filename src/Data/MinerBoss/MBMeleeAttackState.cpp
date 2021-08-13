#include "MBMeleeAttackState.h"
#include "MinerBoss.h"

MBMeleeAttackState::MBMeleeAttackState(Enemy &enemy) : EState(enemy) {

}

std::shared_ptr<EState> MBMeleeAttackState::Update(Enemy &actor) {
    return shared_from_this();
}

void MBMeleeAttackState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}
