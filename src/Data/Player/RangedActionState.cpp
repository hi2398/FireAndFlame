#include "RangedActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "MeleeActionState.h"

std::shared_ptr<State> RangedActionState::Update(Actor &actor) {
    switch (playerCharacter->GetNextAction()) {
        case ACTION::MELEE_ATTACK:
            if constexpr(DEBUG_BUILD) {
                std::cout << "new state: melee" << std::endl;
            }
            return std::make_shared<MeleeActionState>();
        case ACTION::RANGED_ATTACK:
            //TODO: handle ranged state
            return shared_from_this();
        case ACTION::NONE:
            if constexpr(DEBUG_BUILD) {
                std::cout << "new state: idle action" << std::endl;
            }
            return std::make_shared<IdleActionState>();
    }
    throw std::invalid_argument("bad state");
}
