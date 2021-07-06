#include "IdleActionState.h"
#include "../../Global.h"
#include "MeleeActionState.h"
#include "RangedActionState.h"
#include <stdexcept>

std::shared_ptr<State> IdleActionState::Update(Actor &actor) {

    switch (playerCharacter->GetNextAction()) {

        case ACTION::MELEE_ATTACK:
                if constexpr(DEBUG_PLAYER_STATES) {
                    std::cout << "new state: melee" << std::endl;
                }
                return std::make_shared<MeleeActionState>();
        case ACTION::RANGED_ATTACK:
                if constexpr(DEBUG_PLAYER_STATES) {
                    std::cout << "new state: ranged" << std::endl;
                }
                return std::make_shared<RangedActionState>();
        case ACTION::NONE:
        default:
            //TODO: handle idle state
            return shared_from_this();
    }
    throw std::invalid_argument("bad state");
}

void IdleActionState::Draw(Actor& actor) {

}
