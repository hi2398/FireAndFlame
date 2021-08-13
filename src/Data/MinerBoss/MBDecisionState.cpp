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
    if (minerBoss.GetHealth() <= minerBoss.GetMaxHealth()/2 && minerBoss.GetMinerBossPhase()==MinerBossPhase::First){
        minerBoss.SetMinerBossPhase(MinerBossPhase::Transition);
        return std::make_shared<MBPhaseTransitionState>(actor);
    }


    //if (delay==0) return DecideByChance(actor);
    else return shared_from_this();
}

void MBDecisionState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}

std::shared_ptr<EState> MBDecisionState::DecideByChance(Enemy& actor) {
    int switcher = GetRandomValue(1, 3);
    switch (switcher){
        case 1:
            return std::make_shared<MBRangedState>(actor);
        case 2:
            return  std::make_shared<MBMeleeAttackState>(actor);
        case 3:
            return std::make_shared<MBSummonState>(actor);
    }

    throw std::logic_error("couldnt make decision in MBDecisionState");
}
