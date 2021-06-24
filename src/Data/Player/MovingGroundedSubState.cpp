#include "MovingGroundedSubState.h"
#include "IdleGroundedSubState.h"
#include "../../Global.h"

std::shared_ptr<State> MovingGroundedSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    if((actorLastPos.x!=actorPos.x) || (actorLastPos.y!=actorPos.y)) {
        //TODO: do moving state stuff
        return shared_from_this();
    } else {
        if constexpr(DEBUG_BUILD) {
            std::cout << "New State: Idle Grounded" << std::endl;
        }
        return std::make_shared<IdleGroundedSubState>();
    }

}

void MovingGroundedSubState::Draw(Actor& actor) {

}