#include <iostream>
#include "MBDecisionState.h"
#include "MinerBoss.h"
#include "MBPhaseTransitionState.h"
#include "MBRangedState.h"
#include "MBSummonState.h"
#include "MBMeleeAttackState.h"

MBDecisionState::MBDecisionState(Enemy &enemy) : EState(enemy) {

}

std::shared_ptr<EState> MBDecisionState::Update(Enemy &actor) {
    auto minerBoss = dynamic_cast<MinerBoss&>(actor);
    --delay;

    //check if boss should transition to second phase
    if ((minerBoss.GetHealth() <= minerBoss.GetMaxHealth()/2) && (minerBoss.GetMinerBossPhase()==MinerBossPhase::First)) {
        minerBoss.SetMinerBossPhase(MinerBossPhase::Transition);
        return std::make_shared<MBPhaseTransitionState>(actor);
    }


    if (delay==0) return DecideByChance(actor);
    else return shared_from_this();
}

void MBDecisionState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}

std::shared_ptr<EState> MBDecisionState::DecideByChance(Enemy& enemy) {
    auto minerBossPt=dynamic_cast<MinerBoss*>(&enemy);
    int switcher = GetRandomValue(1, 10);
    if (switcher>=9 && minerBossPt->GetMinerBossPhase()==MinerBossPhase::First) return std::make_shared<MBSummonState>(enemy);
    if (switcher>=5) return std::make_shared<MBMeleeAttackState>(enemy);
    else return std::make_shared<MBRangedState>(enemy);

}
