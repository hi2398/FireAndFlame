#include "MBPhaseTransitionState.h"
#include "MinerBoss.h"

MBPhaseTransitionState::MBPhaseTransitionState() {

}

std::shared_ptr<State> MBPhaseTransitionState::Update(Actor &actor) {

    return shared_from_this();
}

void MBPhaseTransitionState::Draw(Actor &actor) {
    auto& minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(actor.GetPosition(), minerBoss.GetTexture());
}
