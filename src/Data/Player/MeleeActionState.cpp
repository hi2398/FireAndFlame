#include "MeleeActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "RangedActionState.h"

std::shared_ptr<State> MeleeActionState::Update(Actor &actor) {
    switch (playerCharacter->GetNextAction()) {

        case ACTION::MELEE_ATTACK:
            //TODO: Handle melee attack
            return shared_from_this();
        case ACTION::RANGED_ATTACK:
            if constexpr(DEBUG_BUILD) {
                std::cout << "new state: ranged" << std::endl;
            }
            return std::make_shared<RangedActionState>();
        case ACTION::NONE:
            if constexpr(DEBUG_BUILD) {
                std::cout << "new state: idle action" << std::endl;
            }
            return std::make_shared<IdleActionState>();
    }
    throw std::invalid_argument("bad state");
}
